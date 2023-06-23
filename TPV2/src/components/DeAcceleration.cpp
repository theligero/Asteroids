#include "DeAcceleration.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include <iostream>

void DeAcceleration::initComponent()
{
	tr = mngr->getComponent<Transform>(ent);
}
