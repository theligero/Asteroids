#include "CollisionsSystem.h"
#include "FighterSystem.h"
#include "AsteroidsSystem.h"
#include "../ecs/Manager.h"
#include "../components/Transform.h"
#include "../components/Health.h"
#include "../utils/Collisions.h"

void CollisionsSystem::receive(const Message& m)
{
	switch (m.id) {
	case _m_MAIN_MENU:
		onRoundOver();
	case _m_IS_GUEST:
		onOnline();
		break;
	case _m_IS_HOST:
		onOnline();
		break;
	case _m_START_GAME:
		onRoundStart();
		break;
	case _m_PAUSE_GAME:
		onRoundOver();
		break;
	case _m_END_GAME:
		onRoundOver();
		break;
	default:
		break;
	}
}

void CollisionsSystem::initSystem()
{
	soloFighter = man->getSystem<FighterSystem>()->getSoloFighter();
	coopFighter = man->getSystem<FighterSystem>()->getFriendFighter();
}

void CollisionsSystem::update()
{
	if (active_) {
		if(state_ == 1){
			for (auto& i : man->getEntities(_grp_ASTEROIDS)) {
				auto astTr = man->getComponent<Transform>(i);
				for (auto& e : man->getEntities(_grp_BULLETS)) {
					auto bullTr = man->getComponent<Transform>(e);
					if (Collisions::collidesWithRotation(bullTr->getPos(), bullTr->getW(), bullTr->getH(), bullTr->getRot(),
						astTr->getPos(), astTr->getW(), astTr->getH(), astTr->getRot())) {
						/*man->setAlive(e, false);
						asteroidManager->onCollision(i);*/
						Message m;
						m.id = _m_ASTEROID_DESTROYED;
						m.asteroid_collision_data.asteroidHit = i;
						m.asteroid_collision_data.bulletHit = e;
						man->send(m);
					}
				}
				auto playerTr = man->getComponent<Transform>(soloFighter);
				if (Collisions::collidesWithRotation(playerTr->getPos(), playerTr->getW(), playerTr->getH(), playerTr->getRot(),
					astTr->getPos(), astTr->getW(), astTr->getH(), astTr->getRot())) {
					/*Message m1;
					m1.id = _m_START_GAME;
					m1.start_game_data.pause = false;
					man->send(m1, true);*/
					Message m2;
					m2.id = _m_FIGHTER_HIT;
					m2.fighter_hit_data.fighterHealth = man->getComponent<Health>(soloFighter);
					man->send(m2);
				}
			}
		}
		else if (state_ == 2) {
			auto coopTr = man->getComponent<Transform>(coopFighter);
			for (auto& e : man->getEntities(_grp_BULLETS)) {
				auto bullTr = man->getComponent<Transform>(e);
				if (Collisions::collidesWithRotation(bullTr->getPos(), bullTr->getW(), bullTr->getH(), bullTr->getRot(),
					coopTr->getPos(), coopTr->getW(), coopTr->getH(), coopTr->getRot())) {
					/*man->setAlive(e, false);
					asteroidManager->onCollision(i);*/
					Message m;
					m.id = _m_FIGHTER_BULLET_HIT;
					m.asteroid_collision_data.bulletHit = e;
					man->send(m);
				}

			}
		}
	}
}

void CollisionsSystem::onOnline()
{
	state_ = 2;
	active_ = true;
}

void CollisionsSystem::onRoundOver()
{
	state_ = 0;
	active_ = false;
}

void CollisionsSystem::onRoundStart()
{
	state_ = 1;
	active_ = true;
}
