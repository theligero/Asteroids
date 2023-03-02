#include "Gun.h"
#include <iostream>
#include "../ecs/Entity.h"

void Gun::initComponent()
{
	tr = ent->getComponent<Transform>(TRANSFORM);
	assert(tr != nullptr);
	clock->reset();
}

void Gun::update()
{
	if (InputHandler::instance()->isKeyDown(SDLK_s) && clock->currTime() > 250) {
		std::cout << "Bala";
		shootSound->play();
		clock->reset();
	}
}
