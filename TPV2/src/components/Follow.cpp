#include "Follow.h"
#include "../ecs/Entity.h"
#include <iostream>

#ifdef SDLUTILS
const float FOLLOWING_SPEED = 1.0f;
#else
const float FOLLOWING_SPEED = 0.01f;
#endif
const int UPDATE_STEP = 300;

void Follow::initComponent()
{
	followedTr = followedEntity->getComponent<Transform>(TRANSFORM);
	assert(followedTr != nullptr);
	tr = ent->getComponent<Transform>(TRANSFORM);
}

//void Follow::update()
//{
//		Vector2D newDir2 = (followedTr->getPos() - tr->getPos()).normalize() * FOLLOWING_SPEED;
//		newDir2.rotate(newDir2.angle(followedTr->getPos() - tr->getPos()) > 0 ? 1.0f : -1.0f);
//		tr->getDir().set(newDir2);
//}
