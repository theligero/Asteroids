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
			man->addComponent<Transform>(aux, Vector2D(x, y),
				Vector2D((rand() % 2), (rand() % 2)), 25, 25, 0);
		#else
			bool goldOrNot = ((rand() % 10) + 1 <= 3) ? true : false;
			aux->addComponent<Transform>(Vector2D(rand() % WINDOW_WIDTH, rand() % WINDOW_HEIGHT),
				Vector2D((rand() % 2) * 0.05f, (rand() % 2) * 0.05f), 25, 25, 0);
		#endif
			man->addComponent<ShowAtOpposideSide>(aux, WINDOW_WIDTH, WINDOW_HEIGHT);
			man->addComponent<Generations>(aux, 2);
			if (goldOrNot) {
				FramedImage *c = man->addComponent<FramedImage>(aux, goldAsteroid, TEXTURE_DESCR[ASTEROID].rows, TEXTURE_DESCR[ASTEROID].cols);
				man->addComponent<Follow>(aux, fighter);
			}
			else man->addComponent<FramedImage>(aux, normalAsteroid, TEXTURE_DESCR[ASTEROID].rows, TEXTURE_DESCR[ASTEROID].cols);
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
		man->setAlive(e, false);
	}
}

void AsteroidsManager::onCollision(Entity* a)
{
	if (man->hasComponent<Generations>(a)) {
		auto aGr = man->getComponent<Generations>(a);
		if (aGr->getGenerations() > 0) {
			auto aTr = man->getComponent<Transform>(a);
			auto aImg = man->getComponent<FramedImage>(a);
			auto aFol = man->getComponent<Follow>(a);
			Entity* aux;
			for (int i = 0; i < 2; ++i) {
				auto r = sdlutils().rand().nextInt(0, 360);
				auto pos = aTr->getPos() + aTr->getDir().rotate(r) * 2 * std::max(aTr->getW(), aTr->getH());
				auto vel = aTr->getDir().rotate(r) * 1.1f;

				aux = man->addEntity(_grp_ASTEROIDS);
				man->addComponent<Transform>(aux, pos, vel, 3* aTr->getW() / 4, 3 * aTr->getW() / 4, r);
				man->addComponent<FramedImage>(aux, aImg->getTexture(), TEXTURE_DESCR[ASTEROID].rows, TEXTURE_DESCR[ASTEROID].cols);
				if (aFol != nullptr) man->addComponent<Follow>(aux, fighter);
				man->addComponent<Generations>(aux, aGr->getGenerations() - 1);
				man->addComponent<ShowAtOpposideSide>(aux, WINDOW_WIDTH, WINDOW_HEIGHT);
			}
		}
	}
	man->setAlive(a, false);
	explosion->play(0, 2);
}
