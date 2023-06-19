#include "FighterCtrl.h"
#include "../ecs/Entity.h"

void FighterCtrl::initComponent()
{
	tr = mngr->getComponent<Transform>(ent);
	assert(tr != nullptr);
	gun = mngr->getComponent<Gun>(ent);
}

//void FighterCtrl::update()
//{
//		if (InputHandler::instance()->isKeyDown(SDLK_w)) {
//			Vector2D newDir = tr->getDir() + Vector2D(0, -1).rotate(tr->getRot()) * thrust;
//			if (newDir.magnitude() > speed_Limit) newDir.normalize()* speed_Limit;
//			tr->getDir().set(newDir);
//			thrustSound->play();
//		}
//		if (InputHandler::instance()->isKeyDown(SDLK_a))
//			tr->setRot(tr->getRot() - 5.0f);
//		else if (InputHandler::instance()->isKeyDown(SDLK_d))
//			tr->setRot(tr->getRot() + 5.0f);
//		if (InputHandler::instance()->isKeyDown(SDLK_SPACE)) {
//			game->getStateMachine()->pushState(new PauseState(game));
//		}
//
//
//	// std::cout << "rotation: " << tr->getRot() << std::endl;
//}
