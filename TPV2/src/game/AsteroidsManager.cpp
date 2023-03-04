#include "AsteroidsManager.h"
#include "../components/Transform.h"
#include "../components/ShowAtOpposideSide.h"
#include "../components/FramedImage.h"
#include "../components/Follow.h"
#include "Game.h"

void AsteroidsManager::createAsteroids(int n)
{
	if (man->getEntities(_grp_ASTEROIDS).size() + n <= MAX_ASTEROIDS) {
		Entity* aux;
		for (int i = 0; i < n; ++i) {
		#ifdef SDLUTILS
			bool goldOrNot = (sdlutils().rand().nextInt(0, 10) < 3) ? true : false;
		#else
			bool goldOrNot = ((rand() % 10) + 1 <= 3) ? true : false;
		#endif
			aux = man->addEntity(_grp_ASTEROIDS);
		#ifdef SDLUTILS
			aux->addComponent<Transform>(TRANSFORM, Vector2D(rand() % WINDOW_WIDTH, rand() % WINDOW_HEIGHT),
				Vector2D((rand() % 2), (rand() % 2)), 25, 25, 0);
		#else
			aux->addComponent<Transform>(TRANSFORM, Vector2D(rand() % WINDOW_WIDTH, rand() % WINDOW_HEIGHT),
				Vector2D((rand() % 2) * 0.05f, (rand() % 2) * 0.05f), 25, 25, 0);
		#endif
			aux->addComponent<ShowAtOpposideSide>(SHOW_AT_OPPOSIDE_SIDE, WINDOW_WIDTH, WINDOW_HEIGHT);
			if (goldOrNot) {
				aux->addComponent<FramedImage>(IMAGE, goldAsteroid, TEXTURE_DESCR[ASTEROID].rows, TEXTURE_DESCR[ASTEROID].cols);
				aux->addComponent<Follow>(FOLLOW, fighter);
			}
			else aux->addComponent<FramedImage>(IMAGE, normalAsteroid, TEXTURE_DESCR[ASTEROID].rows, TEXTURE_DESCR[ASTEROID].cols);
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
}
