#ifndef ASTEROIDS_MANAGER_H_
#define ASTEROIDS_MANAGER_H_

#include "../ecs/Manager.h"

class AsteroidsManager
{
public:
	AsteroidsManager(Manager* m) : man(m) {}
	virtual ~AsteroidsManager() {}
	void createAsteroids(int n);
	void addAsteroidFrequently();
	void destroyAllAsteroids();
	void onCollision(Entity* a);
private:
	Manager* man;
};

#endif /*ASTEROIDS_MANAGER_H_*/