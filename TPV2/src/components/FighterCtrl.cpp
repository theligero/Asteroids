#include "FighterCtrl.h"
#include "../ecs/Entity.h"

void FighterCtrl::initComponent()
{
	tr = mngr->getComponent<Transform>(ent);
	assert(tr != nullptr);
	gun = mngr->getComponent<Gun>(ent);
}

