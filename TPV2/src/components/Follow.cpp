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
