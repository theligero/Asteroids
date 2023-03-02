#include "Follow.h"
#include "../ecs/Entity.h"
#include <iostream>

const float FOLLOWING_SPEED = 0.01f;
const int UPDATE_STEP = 300;

void Follow::initComponent()
{
	followedTr = followedEntity->getComponent<Transform>(TRANSFORM);
	assert(followedTr != nullptr);
	tr = ent->getComponent<Transform>(TRANSFORM);
}

void Follow::update()
{
		Vector2D newDir2 = (followedTr->getPos() - tr->getPos()).normalize() * FOLLOWING_SPEED;
		tr->getDir().set(newDir2);
}
