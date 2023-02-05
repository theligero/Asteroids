#include "ShowAtOpposideSide.h"
#include "../ecs/Entity.h"

ShowAtOpposideSide::ShowAtOpposideSide()
{
	tr = ent->getComponent<Transform>(TRANSFORM);
}

void ShowAtOpposideSide::update()
{
	/*switch (tr->getPos())*/
}
