#include "EndState.h"
#include "PlayState.h"

EndState::EndState(Game* g, bool win)
{
	game = g;

	man = Manager::instance();

	win_ = win;

	infoText = man->addEntity(_grp_INFO);
	man->addComponent<Transform>(infoText, Vector2D(250, 300), Vector2D(0, 0), 300, 100, 0);
	man->addComponent<Image>(infoText, game->getArrayText(PAUSE));
	man->addComponent<PauseCtrl>(infoText, game, false);

	endText = man->addEntity(chooseWinLose(win_));
	man->addComponent<Transform>(endText, Vector2D(250, 400), Vector2D(0, 0), 300, 100, 0);

	if (win_) man->addComponent<Image>(endText, game->getArrayText(WIN));
	else man->addComponent<Image>(endText, game->getArrayText(LOSE));
}


void EndState::update()
{
	Manager::instance()->update(_grp_INFO);
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
	man->setAlive(endText, false);
	man->setAlive(infoText, false);
	std::cout << "saliendo de EndState\n";
	return true;
}

void EndState::backToGame(Game* game)
{
	game->getStateMachine()->changeState(new PlayState(game));
}

grpId_type EndState::chooseWinLose(bool end)
{
	if (end) return _grp_WIN;
	return _grp_LOSE;
}
