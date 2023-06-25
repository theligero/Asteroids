#include "FighterSystem.h"
#include "../ecs/Manager.h"
#include "../components/Transform.h"
#include "../components/DeAcceleration.h"
#include "../components/Health.h"
#include "../components/ShowAtOpposideSide.h"
#include "../components/Gun.h"
#include "../components/FighterCtrl.h"
#include "BulletSystem.h"
#include "OnlineSystem.h"

void FighterSystem::receive(const Message& m)
{
	switch (m.id) {
	case _m_START_GAME:
		onRoundStart();
		break;
	case _m_PAUSE_GAME:
		onRoundOver();
		break;
	case _m_END_GAME:
		onRoundOver();
		break;
	case _m_FIGHTER_HIT:
		onCollision_FighterAsteroid();
		break;
	case _m_FIGHTER_BULLET_HIT:
		onCollision_FighterBullet();
		break;
	case _m_MOVE_ENEMY:
		onMove_Enemy(m.move_enemy_data.enemyPos, m.move_enemy_data.enemyDir, m.move_enemy_data.enemyRot);
	case _m_IS_GUEST:
		onOnline(false);
		break;
	case _m_IS_HOST:
		onOnline(true);
		break;
	case _m_MAIN_MENU:
		onRoundOver();
			break;
	default:
		break;
	}
}

void FighterSystem::initSystem()
{
	hitSound = game->getArraySound(FIGHTER_EXPLOSION);

	//Solo mode
	fighterSolo = man->addEntity(_grp_FIGHTER);
	trSolo = man->addComponent<Transform>(fighterSolo, Vector2D(400, 300), Vector2D(0, 0), 35, 30, 0);
	daSolo = man->addComponent<DeAcceleration>(fighterSolo);
	man->addComponent<Health>(fighterSolo, WINDOW_WIDTH, WINDOW_HEIGHT, game->getArrayTexture(HEART));
	//man->addComponent<Image>(fighterSolo, game->getArrayTexture(FIGHTER));
	saosSolo = man->addComponent<ShowAtOpposideSide>(fighterSolo, WINDOW_WIDTH, WINDOW_HEIGHT);
	gSolo = man->addComponent<Gun>(fighterSolo, game->getArraySound(SHOOT), WINDOW_WIDTH, WINDOW_HEIGHT);
	fcSolo = man->addComponent<FighterCtrl>(fighterSolo, game->getArraySound(THRUST), game);

	//Coop mode
	friendCoop = man->addEntity(_grp_COOP_FIGHTERS);
	trFriend = man->addComponent<Transform>(friendCoop, Vector2D(400, 300), Vector2D(0, 0), 35, 30, 0);
	saosFriend = man->addComponent<ShowAtOpposideSide>(friendCoop, WINDOW_WIDTH, WINDOW_HEIGHT);
	gFriend = man->addComponent<Gun>(friendCoop, game->getArraySound(SHOOT), WINDOW_WIDTH, WINDOW_HEIGHT);
	fcFriend = man->addComponent<FighterCtrl>(friendCoop, game->getArraySound(THRUST), game);
	daFriend = man->addComponent<DeAcceleration>(friendCoop);
	trFriend = man->addComponent<Transform>(friendCoop, Vector2D(400, 300), Vector2D(0, 0), 35, 30, 0);

	enemyCoop = man->addEntity(_grp_COOP_FIGHTERS);
	trEnemy = man->addComponent<Transform>(enemyCoop, Vector2D(400, 300), Vector2D(0, 0), 35, 30, 0);
}

void FighterSystem::update()
{
	if(active_){
		if (state_ == 1) {
			//Caza se mueve
			fighterMovement(trSolo, saosSolo, daSolo);
			//Caza recibe input
			fighterInput(trSolo, fcSolo);
			//Caza ataca
			fighterAttack(trSolo, gSolo);
		}
		else if (state_ == 2) {
			//Caza friend se mueve
			fighterMovement(trFriend, saosFriend, daFriend);
			//Caza friend recibe input
			fighterInput(trFriend, fcFriend);
			//Caza  friend ataca
			onlineFighterAttack(trFriend, gFriend);
		}
	}

}
void FighterSystem::fighterMovement(Transform* tr, ShowAtOpposideSide* saos, DeAcceleration* da)
{
	//Actualizaci�n del transform
	tr->getPos() = tr->getPos() + tr->getDir();
	tr->getCenter() = tr->getPos() + Vector2D(tr->getW() / 2.0f, tr->getH() / 2.0f);

	//Aparece en el otro lado de la pantalla
	if (tr->getPos().getX() > saos->getWindowWidth())
		tr->getPos().setX(-tr->getW());
	else if (tr->getPos().getX() < -tr->getW())
		tr->getPos().setX(saos->getWindowWidth());

	if (tr->getPos().getY() > saos->getWindowHeight())
		tr->getPos().setY(-tr->getH());
	else if (tr->getPos().getY() < -tr->getH())
		tr->getPos().setY(saos->getWindowHeight());

	//Desaceleraci�n
	if (tr->getDir().magnitude() > 0.005)
		tr->getDir().set(tr->getDir() * da->deAcceleration);
	else {
		tr->getDir().set(Vector2D(0, 0));
	}
}
void FighterSystem::fighterInput(Transform* tr, FighterCtrl *fc)
{
	//Control del caza con input del jugador
	if (InputHandler::instance()->isKeyDown(SDLK_w)) {
		Vector2D newDir = tr->getDir() + Vector2D(0, -1).rotate(tr->getRot()) * fc->thrust;
		if (newDir.magnitude() > fc->speed_Limit) newDir.normalize()* fc->speed_Limit;
		tr->getDir().set(newDir);
		fc->getSound()->play();
	}

	if (InputHandler::instance()->isKeyDown(SDLK_a))
		tr->setRot(tr->getRot() - 5.0f);
	else if (InputHandler::instance()->isKeyDown(SDLK_d))
		tr->setRot(tr->getRot() + 5.0f);

	if (InputHandler::instance()->isKeyDown(SDLK_SPACE)) {
		Message m;
		m.id = _m_PAUSE_GAME;
		man->send(m);
	}
}

void FighterSystem::fighterAttack(Transform* tr, Gun* g)
{
	//Disparo
	if (InputHandler::instance()->isKeyDown(SDLK_s) && g->getClock()->currTime() > 250) {
#ifdef _DEBUG
		std::cout << "Bala" << std::endl;
#endif
		Vector2D bulletP = tr->getPos() + Vector2D(trSolo->getW() / 2.0f, tr->getH() / 2.0f)
			- Vector2D(0.0f, tr->getH() / 2.0f + 5.0f + 12.0f).rotate(tr->getRot())
			- Vector2D(2.0f, 10.0f);
#ifdef SDLUTILS
		Vector2D bulletV = Vector2D(0.0f, -1.0f).rotate(tr->getRot()) * 15;
#else
		Vector2D bulletV = Vector2D(0.0f, -1.0f).rotate(tr->getRot()) * 0.09f;
#endif
		Message m;
		m.id = _m_BULLET_SHOT;
		m.shot_bullet_data.pos = bulletP;
		m.shot_bullet_data.vel = bulletV;
		m.shot_bullet_data.width = 5;
		m.shot_bullet_data.height = 20;
		m.shot_bullet_data.rot = tr->getRot();
		man->getSystem<BulletSystem>()->receive(m);
		g->getSound()->play();
		g->getClock()->reset();
	}
}

void FighterSystem::onlineFighterAttack(Transform* tr, Gun* g)
{
	//Disparo
	if (InputHandler::instance()->isKeyDown(SDLK_s) && g->getClock()->currTime() > 250) {
	#ifdef _DEBUG
		std::cout << "Bala" << std::endl;
	#endif
		Vector2D bulletP = tr->getPos() + Vector2D(trSolo->getW() / 2.0f, tr->getH() / 2.0f)
			- Vector2D(0.0f, tr->getH() / 2.0f + 5.0f + 12.0f).rotate(tr->getRot())
			- Vector2D(2.0f, 10.0f);
	#ifdef SDLUTILS
		Vector2D bulletV = Vector2D(0.0f, -1.0f).rotate(tr->getRot()) * 15;
	#else
		Vector2D bulletV = Vector2D(0.0f, -1.0f).rotate(tr->getRot()) * 0.09f;
	#endif
		Message m;
		m.id = _m_BULLET_SHOT;
		m.shot_bullet_data.pos = bulletP;
		m.shot_bullet_data.vel = bulletV;
		m.shot_bullet_data.width = 5;
		m.shot_bullet_data.height = 20;
		m.shot_bullet_data.rot = tr->getRot();
		man->getSystem<BulletSystem>()->receive(m);
		man->getSystem<OnlineSystem>()->receive(m);
		g->getSound()->play();
		g->getClock()->reset();
	}
}
void FighterSystem::onMove_Enemy(Vector2D pos, Vector2D dir, float rot)
{
	trEnemy->setPos(pos);
	trEnemy->setDir(dir);
	trEnemy->setRot(rot);
}
//Asteroide choca contra fighterSolo

void FighterSystem::onCollision_FighterAsteroid()
{
	//Health* h = man->getComponent<Health>(fighterSolo);
	Transform* tr = man->getComponent<Transform>(fighterSolo);
	hitSound->play(0, 1);
	tr->setPos(Vector2D(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2));
	tr->resetDir();
	tr->setRot(0);
	//h->decreaseLives();
	/*if (h->getLives() <= 0) {
		onRoundOver();
		Message m;
		m.id = _m_END_GAME;
		m.end_game_data.win =false;
		m.end_game_data.pause = false;
		man->send(m);
	}*/

}
void FighterSystem::onCollision_FighterBullet()
{
	for(auto nave: man->getEntities(ecs::_grp_COOP_FIGHTERS)){
		Transform* tr = man->getComponent<Transform>(nave);
		hitSound->play(0, 1);
		tr->setPos(Vector2D(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2));
		tr->resetDir();
		tr->setRot(0);
	}
}
void FighterSystem::onOnline(bool host)
{
	host_ = host;

	if (host) {
		trFriend->setPos(Vector2D(0, 300));
		trFriend->setDir(Vector2D(0, 0));
		trFriend->setRot(90);
		trEnemy->setPos(Vector2D(765, 300));
		trEnemy->setDir(Vector2D(0, 0));
		trEnemy->setRot(270);
		trFriend = man->addComponent<Transform>(friendCoop, Vector2D(400, 300), Vector2D(0, 0), 35, 30, 0);
		trEnemy = man->addComponent<Transform>(enemyCoop, Vector2D(400, 300), Vector2D(0, 0), 35, 30, 0);
	}
	else {
		trFriend->setPos(Vector2D(765, 300));
		trFriend->setDir(Vector2D(0, 0));
		trFriend->setRot(270);
		trEnemy->setPos(Vector2D(0, 300));
		trEnemy->setDir(Vector2D(0, 0));
		trEnemy->setRot(90);
		trFriend = man->addComponent<Transform>(friendCoop, Vector2D(765, 300), Vector2D(0, 0), 35, 30, 270);
		trEnemy = man->addComponent<Transform>(enemyCoop, Vector2D(0, 300), Vector2D(0, 0), 35, 30, 90);
	}

	state_ = 2;
	active_ = true;
}
//Fin juego o pausa
void FighterSystem::onRoundOver()
{
	state_ = 0;
	active_ = false;
}
//Inicio de juego o salida de pausa
void FighterSystem::onRoundStart()
{
	state_ = 1;
	active_ = true;
}
