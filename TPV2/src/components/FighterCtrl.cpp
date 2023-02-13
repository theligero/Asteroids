#include "FighterCtrl.h"
#include "../ecs/Entity.h"

void FighterCtrl::initComponent()
{
	tr = ent->getComponent<Transform>(TRANSFORM);
}

void FighterCtrl::update()
{
	// InputHandler::refresh();

	if (InputHandler::instance()->isKeyDown(SDLK_w))
		tr->getDir().set(tr->getDir() + Vector2D(0, -0.05));
	else if (InputHandler::instance()->isKeyDown(SDLK_a))
		tr->getDir().set(tr->getDir() + Vector2D(-0.05, 0));
	else if (InputHandler::instance()->isKeyDown(SDLK_s))
		tr->getDir().set(tr->getDir() + Vector2D(0, 0.05));
	else if (InputHandler::instance()->isKeyDown(SDLK_d))
		tr->getDir().set(tr->getDir() + Vector2D(0.05, 0));
}
