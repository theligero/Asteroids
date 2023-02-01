#ifndef MANAGER_H_
#define MANAGER_H_

#include "Entity.h"

class Entity;

class Manager
{
	Manager();
	virtual ~Manager();

	Entity* addEntity();
	void refresh();
	void update();
	void render();

private:
	std::vector<Entity*> ents;
};

#endif /*MANAGER_H_*/