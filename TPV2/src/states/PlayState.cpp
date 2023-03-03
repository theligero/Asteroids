#include "PlayState.h"
#include "EndState.h"
#include <typeinfo>

PlayState::PlayState(Game* g)
{
	game = g;
	auto& man = *Manager::instance();
	auto fighter = man.addEntity();
	fighter->addComponent<Transform>(TRANSFORM, Vector2D(400, 300), Vector2D(0, 0), 35, 30, 0);
	fighter->addComponent<DeAcceleration>(DEACCELERATION);
	fighter->addComponent<Health>(HEALTH, WINDOW_WIDTH, WINDOW_HEIGHT, game->getArrayTexture(HEART));
	fighter->addComponent<Image>(IMAGE, game->getArrayTexture(FIGHTER));
	fighter->addComponent<ShowAtOpposideSide>(SHOW_AT_OPPOSIDE_SIDE, WINDOW_WIDTH, WINDOW_HEIGHT);
	fighter->addComponent<Gun>(GUN, game->getArraySound(SHOOT), game->getArrayTexture(FIRE), WINDOW_WIDTH, WINDOW_HEIGHT);
	fighter->addComponent<FighterCtrl>(FIGHTER_CTRL, game->getArraySound(THRUST), game);
	fighter->getComponent<Transform>(TRANSFORM)->getPos();


	auto asteroid = man.addEntity(_grp_ASTEROIDS);
	asteroid->addComponent<Transform>(TRANSFORM, Vector2D(250, 250), Vector2D(0, 0), 25, 25, 0);
	asteroid->addComponent<ShowAtOpposideSide>(SHOW_AT_OPPOSIDE_SIDE, WINDOW_WIDTH, WINDOW_HEIGHT);
	asteroid->addComponent<FramedImage>(IMAGE, game->getArrayTexture(ASTEROID), TEXTURE_DESCR[ASTEROID].rows, TEXTURE_DESCR[ASTEROID].cols);
	asteroid->addComponent<Follow>(FOLLOW, fighter);
	

}

void PlayState::update()
{
	Manager::instance()->update();
	InputHandler::instance()->refresh();

	
}

void PlayState::render()
{
	Manager::instance()->render();
}



bool PlayState::onEnter()
{
	std::cout << "Entrando en PlayState\n";
	return true;
}

bool PlayState::onExit()
{
	std::cout << "Saliendo de PlayState\n";
	return true;
}


void PlayState::enterPause()
{
	game->getStateMachine()->pushState(new PauseState(game));
}
