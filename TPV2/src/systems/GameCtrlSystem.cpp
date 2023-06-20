#include "GameCtrlSystem.h"
#include "../sdlutils/InputHandler.h"
#include "FighterSystem.h"
#include "../ecs/Manager.h"
#include "../components/Health.h"


void GameCtrlSystem::receive(const Message& m)
{
	switch (m.id) {
	case _m_NO_MORE_ASTEROIDS:
		onAsteroidsExtinction();
		break;
	case _m_FIGHTER_HIT:
		onCollision_FighterAsteroid(m.fighter_hit_data.fighterHealth);
		break;
	default:
		break;
	}
}

void GameCtrlSystem::initSystem()
{
	infoText = man->addEntity(_grp_INFO);
	man->addComponent<Transform>(infoText, Vector2D(250, 300), Vector2D(0, 0), 300, 100, 0);

	loseText = man->addEntity(_grp_LOSE);
	man->addComponent<Transform>(loseText, Vector2D(250, 400), Vector2D(0, 0), 300, 100, 0);

	winText = man->addEntity(_grp_LOSE);
	man->addComponent<Transform>(winText, Vector2D(250, 400), Vector2D(0, 0), 300, 100, 0);
}

void GameCtrlSystem::update()
{
	Message m;
	if (InputHandler::instance()->isKeyDown(SDLK_SPACE)) {
		switch (state_) {
		case 0:
			state_ = 1;
			m.id = ecs::_m_PAUSE_GAME;
			m.end_game_data.pause = true;
			break;
		case 1:
			state_ = 0;
			m.id = ecs::_m_START_GAME;
			m.start_game_data.pause = true;
			break;
		case 2:
			state_ = 0;
			m.id = ecs::_m_START_GAME;
			m.start_game_data.pause = false;
			break;
		default:
			break;
		}
		man->send(m);
	}
}

void GameCtrlSystem::onCollision_FighterAsteroid(Health* ftrHealth)
{
	ftrHealth->decreaseLives();
	if (ftrHealth->getLives() <= 0) {
	}

	Message m;
	state_ = 2;
	winner_ = 1;
	m.id = ecs::_m_END_GAME;
	m.end_game_data.pause = false;
	m.end_game_data.win = false;
	man->send(m);

}

void GameCtrlSystem::onAsteroidsExtinction()
{
	Message m;
	state_ = 2;
	winner_ = 2;
	m.id = ecs::_m_END_GAME;
	m.end_game_data.pause = false;
	m.end_game_data.win = true;
	man->send(m);
}
