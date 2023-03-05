#include "PauseState.h"
#include "PlayState.h"

PauseState::PauseState(Game* g)
{
	game = g;

	auto& man = *Manager::instance();
	pauseText = man.addEntity(_grp_PAUSE);
	pauseText->addComponent<Transform>(TRANSFORM, Vector2D(250, 300), Vector2D(0, 0), 300, 100, 0);
	pauseText->addComponent<Image>(IMAGE, game->getArrayText(PAUSE));
	pauseText->addComponent<PauseCtrl>(PAUSE_CTRL, game, false);

}

void PauseState::update()
{
	Manager::instance()->update(_grp_PAUSE);
	InputHandler::instance()->refresh();
}

void PauseState::render()
{
	Manager::instance()->render();
}



bool PauseState::onEnter()
{
	std::cout << "entrando en PauseState\n";
	return true;
}

bool PauseState::onExit()
{
	pauseText->setAlive(false);
	std::cout << "saliendo de PauseState\n";
	return true;
}

void PauseState::backToGame(Game* game)
{
	game->getStateMachine()->popState();
}