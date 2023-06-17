#include "DisableOnExit.h"
#include "../ecs/Entity.h"

void DisableOnExit::initComponent()
{
	tr = ent->getComponent<Transform>();
}

void DisableOnExit::update()
{
	// comprobación por si no está dentro de los límites del mapa

	if (!(tr->getPos().getX() > 0 && tr->getPos().getX() < tr->getW() + WindowWidth &&
		tr->getPos().getY() > 0 && tr->getPos().getY() < tr->getH() + WindowHeight)) {
		ent->setAlive(false);
	}
}
