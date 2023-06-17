#include "EndState.h"
#include "PlayState.h"

EndState::EndState(Game* g, bool win)
{
	game = g;

	man = Manager::instance();

	auto pruebatext = man->addEntity(_grp_PAUSE);
	man->addComponent<Transform>(pruebatext, Vector2D(250, 300), Vector2D(0, 0), 300, 100, 0);
	man->addComponent<Image>(pruebatext, game->getArrayText(PAUSE));
	man->addComponent<PauseCtrl>(pruebatext, game, false);

	endText = man->addEntity(_grp_PAUSE);
	man->addComponent<Transform>(endText, Vector2D(250, 400), Vector2D(0, 0), 300, 100, 0);

	if (win) man->addComponent<Image>(endText, game->getArrayText(WIN));
	else man->addComponent<Image>(endText, game->getArrayText(LOSE));
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