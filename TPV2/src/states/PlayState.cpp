#include "PlayState.h"
#include "EndState.h"
#include <typeinfo>
#include "../utils/Collisions.h"

PlayState::PlayState(Game* g)
{
	game = g;
	man = Manager::instance();

	std::cout << "Nueva partida"; 

	fighter = man->addEntity();
	man->addComponent<Transform>(fighter, Vector2D(400, 300), Vector2D(0, 0), 35, 30, 0);
	man->addComponent<DeAcceleration>(fighter);
	man->addComponent<Health>(fighter, WINDOW_WIDTH, WINDOW_HEIGHT, game->getArrayTexture(HEART));
	man->addComponent<Image>(fighter, game->getArrayTexture(FIGHTER));
	man->addComponent<ShowAtOpposideSide>(fighter, WINDOW_WIDTH, WINDOW_HEIGHT);
	man->addComponent<Gun>(fighter, game->getArraySound(SHOOT), game->getArrayTexture(FIRE), WINDOW_WIDTH, WINDOW_HEIGHT);
	man->addComponent<FighterCtrl>(fighter, game->getArraySound(THRUST), game);
	man->getComponent<Transform>(fighter)->getPos();

	asteroidManager = new AsteroidsManager(man->instance(), game->getArrayTexture(ASTEROID_GOLD), 
		game->getArrayTexture(ASTEROID), fighter, game->getArraySound(ASTEROID_EXPLOSION));
}

void PlayState::update()
{
	Manager::instance()->update();
	InputHandler::instance()->refresh();
	checkCollision();
	if (!man->isAlive(fighter)){
		game->getStateMachine()->changeState(new EndState(game, false));
	}
	else if (Manager::instance()->getEntities(_grp_ASTEROIDS).size() == 0) {
		game->getStateMachine()->changeState(new EndState(game, true));
	}
	else 
		asteroidManager->addAsteroidFrequently();
	Manager::instance()->refresh();
	
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
	delete asteroidManager;
	//Manager::instance()->close();
	std::cout << "Saliendo de PlayState\n";
	return true;
}

void PlayState::checkCollision()
{
	for (auto& i :man->getEntities(_grp_ASTEROIDS)) {
		auto astTr = man->getComponent<Transform>(i);
		for (auto& e : man->getEntities(_grp_BULLETS)) {
			auto bullTr = man->getComponent<Transform>(e);
			if (Collisions::collidesWithRotation(bullTr->getPos(), bullTr->getW(), bullTr->getH(), bullTr->getRot(),
				astTr->getPos(), astTr->getW(), astTr->getH(), astTr->getRot())) {
				man->setAlive(e, false);
				asteroidManager->onCollision(i);
			}
		}
		auto playerTr = man->getComponent<Transform>(fighter);
		if (Collisions::collidesWithRotation(playerTr->getPos(), playerTr->getW(), playerTr->getH(), playerTr->getRot(),
			astTr->getPos(), astTr->getW(), astTr->getH(), astTr->getRot())) {
			asteroidManager->destroyAllAsteroids();
			for (auto& a : Manager::instance()->getEntities(_grp_BULLETS)) man->setAlive(a, false);
			auto playerHealth = man->getComponent<Health>(fighter);
			playerHealth->decreaseLives();
			game->getArraySound(FIGHTER_EXPLOSION)->play(0, 1);
			playerTr->setPos(Vector2D(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2));
			playerTr->resetDir();
			playerTr->setRot(0);
			asteroidManager->createAsteroids(10);
			if (playerHealth->getLives() <= 0) {
				man->setAlive(fighter, false);
			}
		}
	}
}


void PlayState::enterPause()
{
	game->getStateMachine()->pushState(new PauseState(game));
}
