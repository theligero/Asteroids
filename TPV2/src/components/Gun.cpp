#include "Gun.h"
#include <iostream>
#include "../ecs/Entity.h"


void Gun::initComponent()
{
	tr = ent->getComponent<Transform>();
	assert(tr != nullptr);
	clock->reset();
}

void Gun::update()
{
	if (InputHandler::instance()->isKeyDown(SDLK_s) && clock->currTime() > 250) {
	#ifdef _DEBUG
		std::cout << "Bala" << std::endl;
	#endif
		auto newBullet = mngr->addEntity(_grp_BULLETS);
		Vector2D bulletP = tr->getPos() + Vector2D(tr->getW() / 2.0f, tr->getH() / 2.0f)
			- Vector2D(0.0f, tr->getH() / 2.0f + 5.0f + 12.0f).rotate(tr->getRot())
			- Vector2D(2.0f, 10.0f);
	#ifdef SDLUTILS
		Vector2D bulletV = Vector2D(0.0f, -1.0f).rotate(tr->getRot()) * 15;
	#else
		Vector2D bulletV = Vector2D(0.0f, -1.0f).rotate(tr->getRot()) * 0.09f;
	#endif
		newBullet->addComponent<Transform>(bulletP, bulletV, 5, 20, tr->getRot());
		newBullet->addComponent<Image>(bulletTexture);
		newBullet->addComponent<DisableOnExit>(WindowWidth, WindowHeight);
		shootSound->play();
		clock->reset();
	}
}
