#include "Gun.h"
#include "../ecs/Entity.h"

void Gun::initComponent()
{
	tr = ent->getComponent<Transform>(TRANSFORM);
	assert(tr != nullptr);
}

void Gun::update()
{

}
