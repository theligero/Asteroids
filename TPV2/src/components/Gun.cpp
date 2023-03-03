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
		auto newBullet = mngr->addEntity(_grp_BULLETS);
		Vector2D bulletP = tr->getCenter() + Vector2D(0.0f, -(tr->getH() / 2.0f + 5.0f)).rotate(tr->getRot());
		Vector2D bulletV = Vector2D(0.0f, -1.0f).rotate(tr->getRot())* 0.09f;
		newBullet->addComponent<Transform>(TRANSFORM, bulletP, bulletV, 25, 25, tr->getRot());
		newBullet->addComponent<Image>(IMAGE, bulletTexture);
		newBullet->addComponent<DisableOnExit>(DISABLE_ON_EXIT, WindowWidth, WindowHeight);
		shootSound->play();
		clock->reset();
	}
}
