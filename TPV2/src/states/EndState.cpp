#include "EndState.h"
#include "PlayState.h"

EndState::EndState(Game* g, bool win)
{
	game = g;

	auto& man = *Manager::instance();

	auto pruebatext = man.addEntity(_grp_PAUSE);
	pruebatext->addComponent<Transform>(TRANSFORM, Vector2D(250, 300), Vector2D(0, 0), 300, 100, 0);
	pruebatext->addComponent<Image>(IMAGE, game->getArrayText(PAUSE));
	pruebatext->addComponent<PauseCtrl>(PAUSE_CTRL, game, false);

	endText = man.addEntity(_grp_PAUSE);
	endText->addComponent<Transform>(TRANSFORM, Vector2D(250, 400), Vector2D(0, 0), 300, 100, 0);
	if (win) {
		endText->addComponent<Image>(IMAGE, game->getArrayText(WIN));
	}
	else {
		endText->addComponent<Image>(IMAGE, game->getArrayText(LOSE));
	}
	

}


void EndState::update()
{
	Manager::instance()->update(_grp_PAUSE);
	InputHandler::instance()->refresh();
}

void EndState::render()
{
	Manager::instance()->render();
}



bool EndState::onEnter()
{
	std::cout << "entrando en PauseState\n";
	return true;
}

bool EndState::onExit()
{
	std::cout << "saliendo de PauseState\n";
	return true;
}

void EndState::backToMenu(Game* game)
{
	game->getStateMachine()->popState();
}