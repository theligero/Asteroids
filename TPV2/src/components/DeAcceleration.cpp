#include "DeAcceleration.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include <iostream>

void DeAcceleration::initComponent()
{
	tr = mngr->getComponent<Transform>(ent);
}

void DeAcceleration::update()
{
	if (tr->getDir().magnitude() > 0.005)
		tr->getDir().set(tr->getDir() * deAcceleration);
	else
		tr->getDir().set(Vector2D(0, 0));
}
