#include "Entity.h"

Entity::Entity(grpId_type gId) : mngr(nullptr), cmps(), currCmps(), alive()
{
	gId_ = gId;
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