#include "AsteroidsSystem.h"
#include "FighterSystem.h"
#include "../ecs/Manager.h"
#include "../components/Transform.h"
#include "../components/Generations.h"
#include "../game/game.h"
#include "../sdlutils/SoundEffect.h"

void AsteroidsSystem::receive(const Message& m)
{
	switch (m.id) {
	case _m_START_GAME: //Si viene de pausa (no crea asteroides) o no(crea asteroides)
		onRoundStart(m.start_game_data.pause);
		break;
	case _m_PAUSE_GAME://si entra en pausa(solo desactiva) o no(elimina todo y desactiva)
		onRoundOver(m.end_game_data.pause);
		break;
	case _m_END_GAME:
		onRoundOver(m.end_game_data.pause);
		break;
	case _m_ASTEROID_DESTROYED:
		onCollision_AsteroidBullet(m.asteroid_collision_data.asteroidHit);
		break;
	default:
		break;
	}
}

void AsteroidsSystem::initSystem()
{
	goldAsteroid = game->getArrayTexture(ASTEROID_GOLD);
	normalAsteroid = game->getArrayTexture(ASTEROID);
	fighter = man->getSystem<FighterSystem>()->getFighter();
	asteroidDestroyed = game->getArraySound(ASTEROID_EXPLOSION);
}

void AsteroidsSystem::update()
{
	if (active_) {
		for (auto e : man->getEntities(ecs::_grp_ASTEROIDS)) {
			Transform* tr = man->getComponent<Transform>(e);
			ShowAtOpposideSide* saos = man->getComponent<ShowAtOpposideSide>(e);
			//Actualizamos posición
			tr->getPos() = tr->getPos() + tr->getDir();
			tr->getCenter() = tr->getPos() + Vector2D(tr->getW() / 2.0f, tr->getH() / 2.0f);
			//Aparece por el otro lado de la pantalla
			if (tr->getPos().getX() > saos->getWindowWidth())
				tr->getPos().setX(-tr->getW());
			else if (tr->getPos().getX() < -tr->getW())
				tr->getPos().setX(saos->getWindowWidth());

			if (tr->getPos().getY() > saos->getWindowHeight())
				tr->getPos().setY(-tr->getH());
			else if (tr->getPos().getY() < -tr->getH())
				tr->getPos().setY(saos->getWindowHeight());

			Follow* f = man->getComponent<Follow>(e);
			if (f != nullptr) {
				Vector2D newDir2 = (f->getFollowed()->getPos() - tr->getPos()).normalize() * FOLLOWING_SPEED;
				newDir2.rotate(newDir2.angle(f->getFollowed()->getPos() - tr->getPos()) > 0 ? 1.0f : -1.0f);
				tr->getDir().set(newDir2);
			}
		}
		addAsteroidFrequently();

	}

}

void AsteroidsSystem::createAsteroids(int n)
{
	Entity* aux;
	for (int i = 0; i < n && numOfAsteroids_ < MAX_ASTEROIDS; ++i) {
		++numOfAsteroids_;
		aux = man->addEntity(_grp_ASTEROIDS);
	#ifdef SDLUTILS
		bool goldOrNot = (sdlutils().rand().nextInt(0, 10) < 3) ? true : false;
		float x = (sdlutils().rand().nextInt(0, 2) == 0) ? 25 : WINDOW_WIDTH - 25;
		float y = (sdlutils().rand().nextInt(0, 2) == 0) ? 25 : WINDOW_HEIGHT - 25;
		man->addComponent<Transform>(aux, Vector2D(x, y),
			Vector2D((rand() % 2), (rand() % 2)), 25, 25, 0);
	#else
		bool goldOrNot = ((rand() % 10) + 1 <= 3) ? true : false;
		aux->addComponent<Transform>(Vector2D(rand() % WINDOW_WIDTH, rand() % WINDOW_HEIGHT),
			Vector2D((rand() % 2) * 0.05f, (rand() % 2) * 0.05f), 25, 25, 0);
	#endif
		man->addComponent<ShowAtOpposideSide>(aux, WINDOW_WIDTH, WINDOW_HEIGHT);
		int nGenerations = sdlutils().rand().nextInt(1, 4);
		man->addComponent<Generations>(aux, nGenerations);
		if (goldOrNot) {
			FramedImage *c = man->addComponent<FramedImage>(aux, goldAsteroid, TEXTURE_DESCR[ASTEROID].rows, TEXTURE_DESCR[ASTEROID].cols);
			man->addComponent<Follow>(aux, fighter);
		}
		else man->addComponent<FramedImage>(aux, normalAsteroid, TEXTURE_DESCR[ASTEROID].rows, TEXTURE_DESCR[ASTEROID].cols);
	}

}

void AsteroidsSystem::onCollision_AsteroidBullet(Entity* a)
{
	if (man->hasComponent<Generations>(a)) {
		auto aGr = man->getComponent<Generations>(a);
		if (aGr->getGenerations() > 0) {
			auto aTr = man->getComponent<Transform>(a);
			auto aImg = man->getComponent<FramedImage>(a);
			auto aFol = man->getComponent<Follow>(a);
			Entity* aux;
			for (int i = 0; i < 2 && numOfAsteroids_ < MAX_ASTEROIDS; ++i) {
				++numOfAsteroids_;
				auto r = sdlutils().rand().nextInt(0, 360);
				auto pos = aTr->getPos() + aTr->getDir().rotate(r) * 2 * std::max(aTr->getW(), aTr->getH());
				auto vel = aTr->getDir().rotate(r) * 1.1f;

				aux = man->addEntity(_grp_ASTEROIDS);
				man->addComponent<Transform>(aux, pos, vel, 3 * aTr->getW() / 4, 3 * aTr->getW() / 4, r);
				man->addComponent<FramedImage>(aux, aImg->getTexture(), TEXTURE_DESCR[ASTEROID].rows, TEXTURE_DESCR[ASTEROID].cols);
				if (aFol != nullptr) man->addComponent<Follow>(aux, fighter);
				man->addComponent<Generations>(aux, aGr->getGenerations() - 1);
				man->addComponent<ShowAtOpposideSide>(aux, WINDOW_WIDTH, WINDOW_HEIGHT);
			}
		}
	}
	--numOfAsteroids_;
	man->setAlive(a, false);
	asteroidDestroyed->play(0, 2);
	if (numOfAsteroids_ <= 0) {
		Message m;
		m.id = _m_NO_MORE_ASTEROIDS;
		man->send(m);
		/*Message m;
		m.id = _m_END_GAME;
		m.end_game_data.win = true;
		m.end_game_data.pause = false;
		man->send(m);*/
	}
}

void AsteroidsSystem::onRoundOver(bool pause)
{
	//No entras en modo Pausa, por tanto eliminas todos los asteroides.
	if (!pause) {
		for (auto e : man->getEntities(ecs::_grp_ASTEROIDS)) {
			man->setAlive(e, false);
		}
		numOfAsteroids_ = 0;
	}
	
	active_ = false;
}

void AsteroidsSystem::onRoundStart(bool pause)
{
	//No vienes de modo Pausa (es inicio de ronda), por tanto creas 10 asteroides.
	if (!pause) {
		for (auto e : man->getEntities(ecs::_grp_ASTEROIDS)) {
			man->setAlive(e, false);
		}
		createAsteroids(10);
	}
	active_ = true;
}

void AsteroidsSystem::addAsteroidFrequently()
{
	if (sdlutils().currRealTime() - lastTime >= 5000) {
		createAsteroids(1);
		lastTime = sdlutils().currRealTime();
	}
}