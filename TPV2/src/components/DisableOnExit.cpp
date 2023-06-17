#include "DisableOnExit.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"

void DisableOnExit::initComponent()
{
	tr = mngr->getComponent<Transform>(ent);
}

void DisableOnExit::update()
{
	// comprobaci�n por si no est� dentro de los l�mites del mapa

	if (!(tr->getPos().getX() > 0 && tr->getPos().getX() < tr->getW() + WindowWidth &&
		tr->getPos().getY() > 0 && tr->getPos().getY() < tr->getH() + WindowHeight)) {
		ent->setAlive(false);
	}
}
