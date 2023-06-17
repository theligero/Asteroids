#include "AsteroidsManager.h"
#include "Game.h"
#include "../components/Transform.h"
#include "../components/ShowAtOpposideSide.h"
#include "../components/FramedImage.h"
#include "../components/Follow.h"
#include "../components/Generations.h"

void AsteroidsManager::createAsteroids(int n)
{
	if (man->getEntities(_grp_ASTEROIDS).size() + n <= MAX_ASTEROIDS) {
		Entity* aux;
		for (int i = 0; i < n; ++i) {
			aux = man->addEntity(_grp_ASTEROIDS);
		#ifdef SDLUTILS
			bool goldOrNot = (sdlutils().rand().nextInt(0, 10) < 3) ? true : false;
			float x = (sdlutils().rand().nextInt(0, 2) == 0) ? 25 : WINDOW_WIDTH - 25;
			float y = (sdlutils().rand().nextInt(0, 2) == 0) ? 25 : WINDOW_HEIGHT - 25;
			aux->addComponent<Transform>(Vector2D(x, y),
				Vector2D((rand() % 2), (rand() % 2)), 25, 25, 0);
		#else
			bool goldOrNot = ((rand() % 10) + 1 <= 3) ? true : false;
			aux->addComponent<Transform>(Vector2D(rand() % WINDOW_WIDTH, rand() % WINDOW_HEIGHT),
				Vector2D((rand() % 2) * 0.05f, (rand() % 2) * 0.05f), 25, 25, 0);
		#endif
			aux->addComponent<ShowAtOpposideSide>(WINDOW_WIDTH, WINDOW_HEIGHT);
			aux->addComponent<Generations>(2);
			if (goldOrNot) {
				aux->addComponent<FramedImage>(goldAsteroid, TEXTURE_DESCR[ASTEROID].rows, TEXTURE_DESCR[ASTEROID].cols);
				aux->addComponent<Follow>(fighter);
			}
			else aux->addComponent<FramedImage>(normalAsteroid, TEXTURE_DESCR[ASTEROID].rows, TEXTURE_DESCR[ASTEROID].cols);
		}
	}
}

void AsteroidsManager::addAsteroidFrequently()
{
	if (sdlutils().currRealTime() - lastTime >= 10000) {
		createAsteroids(1);
		lastTime = sdlutils().currRealTime();
	}
}

void AsteroidsManager::destroyAllAsteroids()
{
	for (auto& e : man->getEntities(_grp_ASTEROIDS)) {
		e->setAlive(false);
	}
}

void AsteroidsManager::onCollision(Entity* a)
{
	if (a->hasComponent<Generations>()) {
		auto aGr = a->getComponent<Generations>();
		if (aGr->getGenerations() > 0) {
			auto aTr = a->getComponent<Transform>();
			auto aImg = a->getComponent<Image>();
			auto aFol = a->getComponent<Follow>();
			Entity* aux;
			for (int i = 0; i < 2; ++i) {
				auto r = sdlutils().rand().nextInt(0, 360);
				auto pos = aTr->getPos() + aTr->getDir().rotate(r) * 2 * std::max(aTr->getW(), aTr->getH());
				auto vel = aTr->getDir().rotate(r) * 1.1f;

				aux = man->addEntity(_grp_ASTEROIDS);
				aux->addComponent<Transform>(pos, vel, 3* aTr->getW() / 4, 3 * aTr->getW() / 4, r);
				aux->addComponent<FramedImage>(aImg->getTexture(), TEXTURE_DESCR[ASTEROID].rows, TEXTURE_DESCR[ASTEROID].cols);
				if (aFol != nullptr) aux->addComponent<Follow>(fighter);
				aux->addComponent<Generations>(aGr->getGenerations() - 1);
				aux->addComponent<ShowAtOpposideSide>(WINDOW_WIDTH, WINDOW_HEIGHT);
			}
		}
	}
	a->setAlive(false);
	explosion->play(0, 2);
}
