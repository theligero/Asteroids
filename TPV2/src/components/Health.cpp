#include "Health.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include <iostream>

void Health::decreaseLives()
{
	if (livesCount > 0) {
		--livesCount;
	}
}

void Health::initComponent()
{
	tr = mngr->getComponent<Transform>(ent);
	assert(tr != nullptr);
}