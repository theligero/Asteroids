#include "FighterCtrl.h"
#include "../ecs/Entity.h"

void FighterCtrl::initComponent()
{
	tr = ent->getComponent<Transform>(TRANSFORM);
}

void FighterCtrl::update()
{
	auto& ih = *InputHandler::instance();

	ih.refresh();

	if (ih.isKeyDown(SDLK_w))
		tr->getDir().setY(tr->getDir().getY() - 0.125);
	else if (ih.isKeyDown(SDLK_s))
		tr->getDir().setY(tr->getDir().getY() + 0.125);
	if (ih.isKeyDown(SDLK_a))
		tr->setRot(tr->getRot() - 5.0f);
	else if (ih.isKeyDown(SDLK_d))
		tr->setRot(tr->getRot() + 5.0f);
}
