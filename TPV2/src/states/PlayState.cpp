#include "PlayState.h"
#include "EndState.h"
#include <typeinfo>
#include "../utils/Collisions.h"

PlayState::PlayState(Game* g)
{
	game = g;
	auto& man = *Manager::instance();

	std::cout << "Nueva partida"; 

	fighter = man.addEntity();
	fighter->addComponent<Transform>(Vector2D(400, 300), Vector2D(0, 0), 35, 30, 0);
	fighter->addComponent<DeAcceleration>();
	fighter->addComponent<Health>(WINDOW_WIDTH, WINDOW_HEIGHT, game->getArrayTexture(HEART));
	fighter->addComponent<Image>(game->getArrayTexture(FIGHTER));
	fighter->addComponent<ShowAtOpposideSide>(WINDOW_WIDTH, WINDOW_HEIGHT);
	fighter->addComponent<Gun>(game->getArraySound(SHOOT), game->getArrayTexture(FIRE), WINDOW_WIDTH, WINDOW_HEIGHT);
	fighter->addComponent<FighterCtrl>(game->getArraySound(THRUST), game);
	fighter->getComponent<Transform>()->getPos();

	asteroidManager = new AsteroidsManager(man.instance(), game->getArrayTexture(ASTEROID_GOLD), 
		game->getArrayTexture(ASTEROID), fighter, game->getArraySound(ASTEROID_EXPLOSION));
}

void PlayState::update()
{
	Manager::instance()->update();
	InputHandler::instance()->refresh();
	checkCollision();
	if (!fighter->isAlive()){
		game->getStateMachine()->changeState(new EndState(game, false));
		auto& man = *Manager::instance();
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
	Manager::instance()->close();
	std::cout << "Saliendo de PlayState\n";
	return true;
}

void PlayState::checkCollision()
{
	for (auto& i : Manager::instance()->getEntities(_grp_ASTEROIDS)) {
		auto astTr = i->getComponent<Transform>();
		for (auto& e : Manager::instance()->getEntities(_grp_BULLETS)) {
			auto bullTr = e->getComponent<Transform>();
			if (Collisions::collidesWithRotation(bullTr->getPos(), bullTr->getW(), bullTr->getH(), bullTr->getRot(),
				astTr->getPos(), astTr->getW(), astTr->getH(), astTr->getRot())) {
				e->setAlive(false);
				asteroidManager->onCollision(i);
			}
		}
		auto playerTr = fighter->getComponent<Transform>();
		if (Collisions::collidesWithRotation(playerTr->getPos(), playerTr->getW(), playerTr->getH(), playerTr->getRot(),
			astTr->getPos(), astTr->getW(), astTr->getH(), astTr->getRot())) {
			asteroidManager->destroyAllAsteroids();
			for (auto& a : Manager::instance()->getEntities(_grp_BULLETS)) a->setAlive(false);
			auto playerHealth = fighter->getComponent<Health>();
			playerHealth->decreaseLives();
			game->getArraySound(FIGHTER_EXPLOSION)->play(0, 1);
			playerTr->setPos(Vector2D(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2));
			playerTr->resetDir();
			playerTr->setRot(0);
			asteroidManager->createAsteroids(10);
			if (playerHealth->getLives() <= 0) {
				fighter->setAlive(false);
			}
		}
	}
}


void PlayState::enterPause()
{
	game->getStateMachine()->pushState(new PauseState(game));
}
