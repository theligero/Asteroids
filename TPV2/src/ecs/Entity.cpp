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

bool Entity::isAlive()
{
	return alive;
}

void Entity::setAlive(const bool& al)
{
	alive = al;
}

inline bool Entity::hasComponent(cmpId_type cId)
{
	return cmps[cId] != nullptr;
}

inline void Entity::update()
{
	auto n = currCmps.size();
	for (auto i = 0u; i < n; ++i) {
		currCmps[i]->update();
	}
}

inline void Entity::render()
{
	auto n = currCmps.size();
	for (auto i = 0u; i < n; ++i) {
		currCmps[i]->render();
	}
}