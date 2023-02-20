#include "DeAcceleration.h"
#include "../ecs/Entity.h"
#include <iostream>

void DeAcceleration::initComponent()
{
	tr = ent->getComponent<Transform>(TRANSFORM);
}

void DeAcceleration::update()
{
	if (lastTime + 10 <= timer->currTime()) {
		if (tr->getDir().magnitude() > 0.0005)
		{
			tr->getDir().set(tr->getDir() * deAcceleration);
			// std::cout << tr->getDir() << std::endl;
		}
		else
			tr->getDir().set(Vector2D(0, 0));
		lastTime = timer->currTime();
		std::cout << timer->currTime() << std::endl;
	}
	
}
