#include "Entity.h"

Entity::Entity() : mngr(nullptr), cmps(), currCmps(), alive()
{
	currCmps.reserve(ecs::maxComponentId);
}

Entity::~Entity()
{
	for (auto c : currCmps) {
		delete c;
	}
}

void Entity::setContext(Manager* man)
{
	mngr = man;
}

void Entity::setAlive(const bool& al)
{
	alive = al;
}

void Entity::update()
{
	auto n = currCmps.size();
	for (auto i = 0u; i < n; ++i) {
		currCmps[i]->update();
	}
}

void Entity::render()
{
	auto n = currCmps.size();
	for (auto i = 0u; i < n; ++i) {
		currCmps[i]->render();
	}
}