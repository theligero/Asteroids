#include "Gun.h"
#include <iostream>
#include "../ecs/Entity.h"


void Gun::initComponent()
{
	tr = mngr->getComponent<Transform>(ent);
	assert(tr != nullptr);
	clock->reset();
}