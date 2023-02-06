#include <cassert>
#include "ShowAtOpposideSide.h"
#include "../ecs/Entity.h"

ShowAtOpposideSide::ShowAtOpposideSide()
{
	tr = ent->getComponent<Transform>(TRANSFORM);
	assert(tr != nullptr);
}

void ShowAtOpposideSide::update()
{
	if (tr->getW() + tr->getPos().getY() > WindowWidth)
		tr->getPos().setY(-tr->getW());
	else if (tr->getPos().getY() < -tr->getW())
		tr->getPos().setY(WindowWidth + tr->getW());
	
	if (tr->getH() + tr->getPos().getX() > WindowHeight)
		tr->getPos().setX(-tr->getH());
	else if (tr->getPos().getX() < -tr->getH())
		tr->getPos().setX(WindowHeight + tr->getH());
}
