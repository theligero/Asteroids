#include "FighterSystem.h"
#include "../ecs/Manager.h"
#include "../components/Transform.h"
#include "../components/DeAcceleration.h"
#include "../components/Health.h"
#include "../components/Image.h"
#include "../components/ShowAtOpposideSide.h"
#include "../components/Gun.h"
#include "../components/FighterCtrl.h"
#include "BulletSystem.h"

void FighterSystem::receive(const Message& m)
{
	switch (m.id) {
	case _m_STÄRT_GAME:
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
	default:
		break;
	}
}

void FighterSystem::initSystem()
{
	fighter = man->addEntity(_grp_FIGHTER);
	tr = man->addComponent<Transform>(fighter, Vector2D(400, 300), Vector2D(0, 0), 35, 30, 0);
	da = man->addComponent<DeAcceleration>(fighter);
	man->addComponent<Health>(fighter, WINDOW_WIDTH, WINDOW_HEIGHT, game->getArrayTexture(HEART));
	//man->addComponent<Image>(fighter, game->getArrayTexture(FIGHTER));
	saos = man->addComponent<ShowAtOpposideSide>(fighter, WINDOW_WIDTH, WINDOW_HEIGHT);
	g = man->addComponent<Gun>(fighter, game->getArraySound(SHOOT), game->getArrayTexture(FIRE), WINDOW_WIDTH, WINDOW_HEIGHT);
	fc = man->addComponent<FighterCtrl>(fighter, game->getArraySound(THRUST), game);

}

void FighterSystem::update()
{
	if(active_){
		//Caza se mueve
		fighterMovement();
		//Caza recibe input
		fighterInput();
		//Caza ataca
		fighterAttack();
	}

}
void FighterSystem::fighterMovement()
{
	//Actualización del transform
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

	//Desaceleración
	if (tr->getDir().magnitude() > 0.005)
		tr->getDir().set(tr->getDir() * da->deAcceleration);
	else {
		tr->getDir().set(Vector2D(0, 0));
	}
}
void FighterSystem::fighterInput()
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
		game->getStateMachine()->pushState(new PauseState(game));
	}
}
void FighterSystem::fighterAttack()
{
	//Disparo
	if (InputHandler::instance()->isKeyDown(SDLK_s) && g->getClock()->currTime() > 250) {
	#ifdef _DEBUG
		std::cout << "Bala" << std::endl;
	#endif
		Vector2D bulletP = tr->getPos() + Vector2D(tr->getW() / 2.0f, tr->getH() / 2.0f)
			- Vector2D(0.0f, tr->getH() / 2.0f + 5.0f + 12.0f).rotate(tr->getRot())
			- Vector2D(2.0f, 10.0f);
	#ifdef SDLUTILS
		Vector2D bulletV = Vector2D(0.0f, -1.0f).rotate(tr->getRot()) * 15;
	#else
		Vector2D bulletV = Vector2D(0.0f, -1.0f).rotate(tr->getRot()) * 0.09f;
	#endif
		Message m;
		m.id = _m_BULLET_SHOT;
		m.shot_bullet_data.gId = _grp_BULLETS;
		m.shot_bullet_data.pos = bulletP;
		m.shot_bullet_data.vel = bulletV;
		m.shot_bullet_data.bulletTexture = g->getBulletTexture();
		m.shot_bullet_data.windowHeight = g->getWindowHeight();
		m.shot_bullet_data.windowWidth = g->getWindowWidth();
		m.shot_bullet_data.width = 5;
		m.shot_bullet_data.height = 20;
		m.shot_bullet_data.rot = tr->getRot();
		man->getSystem<BulletSystem>()->receive(m);
		g->getSound()->play();
		g->getClock()->reset();
	}
}
//Asteroide choca contra fighter

void FighterSystem::onCollision_FighterAsteroid()
{
	Health* h = man->getComponent<Health>(fighter);
	Transform* tr = man->getComponent<Transform>(fighter);
	h->decreaseLives();
	hitSound->play(0, 1);
	tr->setPos(Vector2D(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2));
	tr->resetDir();
	tr->setRot(0);
	if (h->getLives() <= 0) {
		onRoundOver();
		Message m;
		m.id = _m_END_GAME;
		m.end_game_data.win =false;
		man->send(m);
	}

}
//Fin juego o pausa
void FighterSystem::onRoundOver()
{
	active_ = false;
}
//Inicio de juego o salida de pausa
void FighterSystem::onRoundStart()
{
	active_ = true;
}
