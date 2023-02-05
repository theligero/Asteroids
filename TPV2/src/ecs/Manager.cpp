#include "Manager.h"

Manager::Manager() : ents()
{
	ents.reserve(100);
}

Manager::~Manager()
{
	for (auto& e : ents) {
		delete e;
	}
}

Entity* Manager::addEntity()
{
	Entity* e = new Entity();
	e->setAlive(true);
	e->setContext(this);
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
	auto n = ents.size();
	for (auto i = 0u; i < n; ++i) {
		ents[i]->update();
	}
}

void Manager::render()
{
	auto n = ents.size();
	for (auto i = 0u; i < n; ++i) {
		ents[i]->render();
	}
}
