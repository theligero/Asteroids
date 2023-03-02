#include "FighterCtrl.h"
#include "../ecs/Entity.h"

const float thrust = 0.2f;
const float speedLimit = 3.0f;

void FighterCtrl::initComponent()
{
	tr = ent->getComponent<Transform>(TRANSFORM);

}

void FighterCtrl::update()
{
	auto& ih = *InputHandler::instance();

	ih.refresh();

	if (ih.isKeyDown(SDLK_w)) {
		Vector2D newDir = tr->getDir() + Vector2D(0, -1).rotate(tr->getRot()) * thrust;
		if (newDir.magnitude() > speedLimit) newDir.normalize()* speedLimit;
		tr->getDir().set(newDir);
		thrustSound->play();
	}
	if (ih.isKeyDown(SDLK_a))
		tr->setRot(tr->getRot() - 5.0f);
	else if (ih.isKeyDown(SDLK_d))
		tr->setRot(tr->getRot() + 5.0f);

	// std::cout << "rotation: " << tr->getRot() << std::endl;
}
