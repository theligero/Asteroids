#include "Entity.h"

Entity::Entity() : mngr(nullptr), currCmps(), alive()
{
	// currCmps.reserve(8);
}

Entity::~Entity()
{

}

bool Entity::isAlive()
{
	return alive;
}

void Entity::setAlive(const bool& al)
{
	alive = al;
}

template<typename T, typename ...Ts>
inline T* Entity::addComponent()
{
	return nullptr;
}

inline void Entity::deleteComponent()
{

}

template<typename T>
inline T* Entity::getComponent()
{
	return nullptr;
}

inline bool Entity::hasComponent()
{
	return false;
}

void Entity::update()
{

}

void Entity::render()
{

}