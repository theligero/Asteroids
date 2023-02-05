#include "DisableOnExit.h"
#include "../ecs/Entity.h"

DisableOnExit::DisableOnExit()
{
	tr = ent->getComponent<Transform>(TRANSFORM);
	widthTr = tr->getW();
	heightTr = tr->getH();
}

void DisableOnExit::update()
{
	// comprobación por si no está dentro de los límites del mapa
	//if (...)
	//	// algo
	//else if (...)
	//	// otra cosa
	//else if (...)
	//	// otra cosa
	//else if (...)
	//	// otra cosa
}
