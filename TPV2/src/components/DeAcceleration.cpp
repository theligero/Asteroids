#include "DeAcceleration.h"
#include "../ecs/Entity.h"
#include <iostream>

void DeAcceleration::initComponent()
{
	tr = ent->getComponent<Transform>(TRANSFORM);
}

void DeAcceleration::update()
{
	if (tr->getDir().magnitude() > 0.05)
	{
		tr->getDir().set(tr->getDir() * deAcceleration);
		std::cout << tr->getDir() << std::endl;
	}
	else
		tr->getDir().set(Vector2D(0, 0));
}
