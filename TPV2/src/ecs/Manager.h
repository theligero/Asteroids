#ifndef MANAGER_H_
#define MANAGER_H_

#include "Entity.h"
#include "../utils/Singleton.h"
#include <vector>

class Manager : public Singleton<Manager>
{
public:
	virtual ~Manager();

	Entity* addEntity();
	void refresh();
	void update();
	void render();

private:
	friend Singleton<Manager>;
	Manager();
	std::vector<Entity*> ents;
};

#endif /*MANAGER_H_*/