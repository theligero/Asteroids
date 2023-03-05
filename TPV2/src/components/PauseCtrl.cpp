#include "PauseCtrl.h"

void PauseCtrl::initComponent()
{
	tr = ent->getComponent<Transform>(TRANSFORM);
	assert(tr != nullptr);
}

void PauseCtrl::update()
{
	if (isPaused) {
		if (InputHandler::instance()->isKeyDown(SDLK_ESCAPE)) {
			game->getStateMachine()->popState();
		}
	}
	else {
		if (InputHandler::instance()->isKeyDown(SDLK_ESCAPE)) {
			Manager::instance()->killEveryEntity();
			game->getStateMachine()->changeState(new PauseState(game));
		}
	}
	
}
