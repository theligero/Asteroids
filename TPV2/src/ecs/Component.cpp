#include "Component.h"

Component::Component()
{

}

Component::~Component()
{

}

inline void Component::setContext(Entity* e, Manager* m)
{
	ent = e; mngr = m;
}

void Component::update()
{

}

void Component::render()
{

}
