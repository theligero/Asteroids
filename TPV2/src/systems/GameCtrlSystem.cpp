#include "GameCtrlSystem.h"
#include "../sdlutils/InputHandler.h"
#include "FighterSystem.h"
#include "../ecs/Manager.h"
#include "../game/game.h"
#include "../components/Health.h"
#include "../components/Clickable.h"

void GameCtrlSystem::receive(const Message& m)
{
	switch (m.id) {
	case _m_NO_MORE_ASTEROIDS:
		onAsteroidsExtinction();
		break;
	case _m_FIGHTER_HIT:
		onCollision_FighterAsteroid(m.fighter_hit_data.fighterHealth);
		break;
	case _m_FIGHTER_BULLET_HIT:
		onFighterBulletDeath();
		break;
	case _m_ENEMY_DEAD:
		onFighterBulletDeath();
		break;
	default:
		break;
	}
}

void GameCtrlSystem::initSystem()
{
	fighter = man->getSystem<FighterSystem>()->getSoloFighter();

	infoText = man->addEntity(_grp_INFO);
	man->addComponent<Transform>(infoText, Vector2D(250, 300), Vector2D(0, 0), 300, 100, 0);

	loseText = man->addEntity(_grp_LOSE);
	man->addComponent<Transform>(loseText, Vector2D(250, 400), Vector2D(0, 0), 300, 100, 0);

	winText = man->addEntity(_grp_WIN);
	man->addComponent<Transform>(winText, Vector2D(250, 400), Vector2D(0, 0), 300, 100, 0);

	title= man->addEntity(_grp_TITLE);
	man->addComponent<Transform>(title, Vector2D(WINDOW_WIDTH / 2 - 300, WINDOW_HEIGHT / 8), Vector2D(), 600, 100, 0);


	jugarSolo = man->addEntity(_grp_SOLO_BUTTON);
	man->addComponent<Transform>(jugarSolo, Vector2D(WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 2 - 75), Vector2D(), 200, 100, 0);
	man->addComponent<Clickable>(jugarSolo);

	jugarCoop = man->addEntity(_grp_COOP_BUTTON);
	auto trCoop = man->addComponent<Transform>(jugarCoop, Vector2D(WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 2 + 75), Vector2D(), 200, 100, 0);
	man->addComponent<Clickable>(jugarCoop);
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
			man->getComponent<Health>(fighter)->resetLives();
			state_ = 3;
			m.id = ecs::_m_MAIN_MENU;
			break;
		default:
			break;
		}
		man->send(m);
	}
	if(state_ == 3){
		if (InputHandler::instance()->mouseMotionEvent() == true) {
			SDL_GetMouseState(&mouseX, &mouseY);
		}
		if (InputHandler::instance()->getMouseButtonState(InputHandler::LEFT)) {
			for (auto& e : man->getEntities(_grp_SOLO_BUTTON)) {
				auto c = man->getComponent<Clickable>(e);
				if (c->inTheRightX(mouseX) && c->inTheRightY(mouseY)) {
					state_ = 0;
					Message m;
					m.id = _m_START_GAME;
					m.start_game_data.pause = false;
					man->send(m, true);
				}
			}
			for (auto& e : man->getEntities(_grp_COOP_BUTTON)) {
				auto c = man->getComponent<Clickable>(e);
				if (c->inTheRightX(mouseX) && c->inTheRightY(mouseY)) {
					// std::cin.ignore();
					std::string name;
					std::cout << "Introduzca su nombre de usuario: ";
					std::cin >> name;
					std::cout << "Tu nombre de usuario es: " << name << std::endl;

					char a;
					std::cout << "Quieres ser el host o el invitado? [H/I]: ";
					std::cin >> a;
					std::cout << std::endl;

					state_ = 4;
					Message m;
					if (a == 'H' || a == 'h') {
						m.id = _m_IS_HOST;
						m.online_init_data.name = name;
						m.online_init_data.host = true;
					}
					else {
						m.id = _m_IS_GUEST;
						m.online_init_data.name = name;
						m.online_init_data.host = false;
					}
					man->send(m, true);
				}
			}
		}
	}
}

void GameCtrlSystem::onCollision_FighterAsteroid(Health* ftrHealth)
{
	ftrHealth->decreaseLives();
	if (ftrHealth->getLives() <= 0) {
		Message m;
		state_ = 2;
		winner_ = 1;
		m.id = ecs::_m_END_GAME;
		m.end_game_data.pause = false;
		m.end_game_data.win = false;
		man->send(m);
	}
	else {
		Message m1;
		m1.id = ecs::_m_START_GAME;
		m1.start_game_data.pause = false;
		man->send(m1);
	}
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

void GameCtrlSystem::onFighterBulletDeath()
{
	Message m;
	state_ = 3;
	winner_ = 0;
	m.id = ecs::_m_MAIN_MENU;
	man->send(m, true);
}
