#include "EndState.h"
#include "PlayState.h"

EndState::EndState(Game* g, bool win)
{
	game = g;

	auto& man = *Manager::instance();

	auto pruebatext = man.addEntity(_grp_PAUSE);
	pruebatext->addComponent<Transform>(Vector2D(250, 300), Vector2D(0, 0), 300, 100, 0);
	pruebatext->addComponent<Image>(game->getArrayText(PAUSE));
	pruebatext->addComponent<PauseCtrl>(game, false);

	endText = man.addEntity(_grp_PAUSE);
	endText->addComponent<Transform>(Vector2D(250, 400), Vector2D(0, 0), 300, 100, 0);

	if (win) endText->addComponent<Image>(game->getArrayText(WIN));
	else endText->addComponent<Image>(game->getArrayText(LOSE));
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
	std::cout << "entrando en EndState\n";
	return true;
}

bool EndState::onExit()
{
	std::cout << "saliendo de EndState\n";
	return true;
}

void EndState::backToMenu(Game* game)
{
	game->getStateMachine()->popState();
}