#include "Follow.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include <iostream>



void Follow::initComponent()
{
	followedTr = mngr->getComponent<Transform>(followedEntity);
	assert(followedTr != nullptr);
	tr = mngr->getComponent<Transform>(ent);
}

void Follow::update()
{
		Vector2D newDir2 = (followedTr->getPos() - tr->getPos()).normalize() * FOLLOWING_SPEED;
		newDir2.rotate(newDir2.angle(followedTr->getPos() - tr->getPos()) > 0 ? 1.0f : -1.0f);
		tr->getDir().set(newDir2);
}
