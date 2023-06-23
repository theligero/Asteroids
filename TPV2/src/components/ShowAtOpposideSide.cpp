#include <cassert>
#include "ShowAtOpposideSide.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"

void ShowAtOpposideSide::initComponent() 
{
	tr = mngr->getComponent<Transform>(ent);
	assert(tr != nullptr);
}
