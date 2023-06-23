#include "DisableOnExit.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"

void DisableOnExit::initComponent()
{
	tr = mngr->getComponent<Transform>(ent);
}