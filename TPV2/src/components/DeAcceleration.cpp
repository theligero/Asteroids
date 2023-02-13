#include "DeAcceleration.h"
#include "../ecs/Entity.h"

DeAcceleration::DeAcceleration()
{
	tr = ent->getComponent<Transform>(TRANSFORM);
}

void DeAcceleration::update()
{
	if (tr->getDir().magnitude() > 0.05)
		tr->getDir().set(tr->getDir() * deAcceleration);
	else
		tr->getDir().set(Vector2D(0, 0));
}
