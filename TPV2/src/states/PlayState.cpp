#include "PlayState.h"
#include "EndState.h"
#include <typeinfo>
#include "../utils/Collisions.h"

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

	asteroidManager = new AsteroidsManager(man.instance(), game->getArrayTexture(ASTEROID_GOLD), 
		game->getArrayTexture(ASTEROID), fighter);
}

void PlayState::update()
{
	Manager::instance()->update();
	InputHandler::instance()->refresh();
	checkCollision();
	Manager::instance()->refresh();
	if (Manager::instance()->getEntities(_grp_ASTEROIDS).size() == 0)
		game->getStateMachine()->popState();
	else
		asteroidManager->addAsteroidFrequently();
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

void PlayState::checkCollision()
{
	for (auto& e : Manager::instance()->getEntities(_grp_BULLETS)) {
		auto bullTr = e->getComponent<Transform>(TRANSFORM);
		for (auto& i : Manager::instance()->getEntities(_grp_ASTEROIDS)) {
			auto astTr = i->getComponent<Transform>(TRANSFORM);
			if (Collisions::collidesWithRotation(bullTr->getPos(), bullTr->getW(), bullTr->getH(), bullTr->getRot(),
					astTr->getPos(), astTr->getW(), astTr->getH(), astTr->getRot())) {
				e->setAlive(false);
				asteroidManager->onCollision(i);
			}
		}
	}
}


void PlayState::enterPause()
{
	game->getStateMachine()->pushState(new PauseState(game));
}
