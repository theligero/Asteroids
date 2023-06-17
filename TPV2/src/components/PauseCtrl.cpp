#include "PauseCtrl.h"

void PauseCtrl::initComponent()
{
	tr = mngr->getComponent<Transform>(ent);
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
			game->getStateMachine()->changeState(new PauseState(game));
		}
	}
	
}
