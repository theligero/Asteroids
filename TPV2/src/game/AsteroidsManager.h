#ifndef ASTEROIDS_MANAGER_H_
#define ASTEROIDS_MANAGER_H_

#include "../ecs/Manager.h"
#ifdef SDLUTILS
#include "../sdlutils/SDLUtils.h"
#else
#include "../sdlutils/VirtualTimer.h"
#endif

const int MAX_ASTEROIDS = 30;
const int INI_ASTEROIDS = 10;

class Texture;

class AsteroidsManager
{
public:
	AsteroidsManager(Manager* m, Texture* gold, Texture* ast, Entity* f, SoundEffect* s) : 
		man(m), goldAsteroid(gold), normalAsteroid(ast), fighter(f), explosion(s) { 
		createAsteroids(INI_ASTEROIDS); 
	#ifdef SDLUTILS
		lastTime = sdlutils().currRealTime(); 
	#else
		lastTime = clock->currTime();
	#endif
	}
	virtual ~AsteroidsManager() {}
	void createAsteroids(int n);
	void addAsteroidFrequently();
	void destroyAllAsteroids();
	void onCollision(Entity* a);
private:
#ifndef SDLUTILS
	VirtualTimer* clock;
#endif
	SoundEffect* explosion;
	Entity* fighter;
	Texture* normalAsteroid;
	Texture* goldAsteroid;
	Manager* man;
	int numAsteroids;
	int lastTime;
};

#endif /*ASTEROIDS_MANAGER_H_*/