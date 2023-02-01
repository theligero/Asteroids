#include "Manager.h"

Manager::Manager() 
{

}

Manager::~Manager()
{

}

Entity* Manager::addEntity()
{
	Entity* e = new Entity();
	e->setAlive(true);
	// e->setContext(this);
	ents.push_back(e);
	return e;
}

void Manager::refresh()
{
	ents.erase(
		std::remove_if(ents.begin(), ents.end(), [](Entity* e) {
			if (e->isAlive()) {
				return false;
			}
			else {
				delete e;
				return true;
			}
			}),
		ents.end());
}

void Manager::update()
{

}

void Manager::render()
{

}
