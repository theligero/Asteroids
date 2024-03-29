#include "DisableOnExit.h"
#include "../ecs/Entity.h"

void DisableOnExit::initComponent()
{
	tr = ent->getComponent<Transform>(TRANSFORM);
}

void DisableOnExit::update()
{
	// comprobaci�n por si no est� dentro de los l�mites del mapa

	if (!(tr->getPos().getX() > 0 && tr->getPos().getX() < tr->getW() + WindowWidth &&
		tr->getPos().getY() > 0 && tr->getPos().getY() < tr->getH() + WindowHeight)) {
		ent->setAlive(false);
	}
}
