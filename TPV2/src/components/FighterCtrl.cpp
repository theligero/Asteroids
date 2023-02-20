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

	if (ih.isKeyDown(SDLK_w)) {
		float _x = -cos((tr->getRot() + 90) * M_PI / 180) * 0.15;
		float _y = -sin((tr->getRot() + 90) * M_PI / 180) * 0.15;
		std::cout << _x << " " << _y << std::endl;
		tr->getDir().set(Vector2D(_x, _y));
	}
	if (ih.isKeyDown(SDLK_a))
		tr->setRot(tr->getRot() - 5.0f);
	else if (ih.isKeyDown(SDLK_d))
		tr->setRot(tr->getRot() + 5.0f);

	// std::cout << "rotation: " << tr->getRot() << std::endl;
}
