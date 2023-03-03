#include "PauseState.h"
#include "PlayState.h"

PauseState::PauseState(Game* g)
{
	game = g;

	auto& man = *Manager::instance();
	auto pause = man.addEntity(_grp_PAUSE);
	pause->addComponent<Transform>(TRANSFORM, Vector2D(400, 300), Vector2D(0, 0), 35, 30, 0);
	pause->addComponent<Image>(IMAGE, game->getArrayText(PAUSE));
	pause->addComponent<FighterCtrl>(FIGHTER_CTRL, game->getArraySound(THRUST), game);

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
	std::cout << "saliendo de PauseState\n";
	return true;
}

void PauseState::backToGame(Game* game)
{
	game->getStateMachine()->popState();
}