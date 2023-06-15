#include <cassert>
#include "ShowAtOpposideSide.h"
#include "../ecs/Entity.h"

void ShowAtOpposideSide::initComponent() 
{
	tr = ent->getComponent<Transform>(TRANSFORM);
	assert(tr != nullptr);
}

void ShowAtOpposideSide::update()
{	
	if (tr->getPos().getX() > WindowWidth)
		tr->getPos().setX(-tr->getW());
	else if (tr->getPos().getX() < -tr->getW())
		tr->getPos().setX(WindowWidth);

	if (tr->getPos().getY() > WindowHeight)
		tr->getPos().setY(-tr->getH());
	else if (tr->getPos().getY() < -tr->getH())
		tr->getPos().setY(WindowHeight);
}
