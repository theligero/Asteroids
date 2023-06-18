#include "PauseCtrl.h"

void PauseCtrl::initComponent()
{
	tr = mngr->getComponent<Transform>(ent);
	assert(tr != nullptr);
}

void PauseCtrl::update()
{
	if (InputHandler::instance()->isKeyDown(SDLK_ESCAPE)) {
		game->getStateMachine()->currentState()->backToGame(game);
	}
}
