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
	// comprobaci�n por si no est� dentro de los l�mites del mapa
	//if (...)
	//	// algo
	//else if (...)
	//	// otra cosa
	//else if (...)
	//	// otra cosa
	//else if (...)
	//	// otra cosa
}
