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

//template<typename T, typename ...Ts>
//inline T* Entity::addComponent(cmpId_type cId, Ts &&…args)
//{
//	T* c = new T(std::forward<Ts>(args)...);
//
//	removeComponent(cId);
//
//	currCmps.push_back(c);
//	cmps[cId] = c;
//
//	c->setContext(this, mngr);
//	c->initComponent();
//
//	return c;
//}

inline void Entity::removeComponent(cmpId_type cId)
{
	if (cmps[cId] != nullptr) {
		auto it = std::find(currCmps.begin(), currCmps.end(), cmps[cId]);
		currCmps.erase(it);
		delete cmps[cId];
		cmps[cId] = nullptr;
	}
}

template<typename T>
inline T* Entity::getComponent(cmpId_type cId)
{
	return static_cast<T*>(cmps[cId]);
}

inline bool Entity::hasComponent(cmpId_type cId)
{
	return cmps[cId] != nullptr;
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