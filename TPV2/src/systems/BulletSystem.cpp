#include "BulletSystem.h"
#include "../ecs/Manager.h"
#include "../components/Transform.h"
#include "../components/DisableOnExit.h"

void BulletSystem::receive(const Message& m)
{
	switch (m.id) {
	case _m_START_GAME: //Si viene de pausa (no crea asteroides) o no(crea asteroides)
		onRoundStart(m.start_game_data.pause);
		break;
	case _m_IS_GUEST:
		onOnline();
		break;
	case _m_IS_HOST:
		onOnline();
		break;
	case _m_MAIN_MENU:
		onOnlineOver();
	case _m_PAUSE_GAME:
		onRoundOver(m.end_game_data.pause);
		break;
	case _m_END_GAME:
		onRoundOver(m.end_game_data.pause);
		break;
	case _m_ASTEROID_DESTROYED:
		onCollision_BulletAsteroid(m.asteroid_collision_data.bulletHit);
		break;
	case _m_FIGHTER_BULLET_HIT:
		onCollision_Bullet_Fighter(m.asteroid_collision_data.bulletHit);
		break;
	case _m_BULLET_SHOT:
		shoot(m.shot_bullet_data.pos, m.shot_bullet_data.vel, m.shot_bullet_data.width, m.shot_bullet_data.height, m.shot_bullet_data.rot);
		break;
	default:
		break;
	}
}

void BulletSystem::initSystem()
{
}

void BulletSystem::update()
{
	if (active_) {
		for (auto e : man->getEntities(ecs::_grp_BULLETS)) {
			Transform* tr = man->getComponent<Transform>(e);
			DisableOnExit* doe = man->getComponent<DisableOnExit>(e);
			//Actualizamos posici�n
			tr->getPos() = tr->getPos() + tr->getDir();
			tr->getCenter() = tr->getPos() + Vector2D(tr->getW() / 2.0f, tr->getH() / 2.0f);
			//Si la bala sale de la pantalla la desactivamos.
			if (!(tr->getPos().getX() > 0 && tr->getPos().getX() < tr->getW() + doe->getWindowWidth() &&
				tr->getPos().getY() > 0 && tr->getPos().getY() < tr->getH() + doe->getWindowHeight())) {
				man->setAlive(e, false);
			}
		}
	}
}

void BulletSystem::shoot(Vector2D pos, Vector2D vel, double width, double height, float rot)
{
	Entity* newBullet = man->addEntity(_grp_BULLETS);
	man->addComponent<Transform>(newBullet, pos, vel, 5, 20, rot);
	man->addComponent<DisableOnExit>(newBullet, wWidth, wHeight);
}

void BulletSystem::onOnline()
{
	for (auto e : man->getEntities(ecs::_grp_BULLETS)) {
		man->setAlive(e, false);
	}
	active_ = true;
}

void BulletSystem::onOnlineOver()
{
	for (auto e : man->getEntities(ecs::_grp_BULLETS)) {
		man->setAlive(e, false);
	}
	active_ = false;
}

void BulletSystem::onCollision_BulletAsteroid(Entity* b)
{
	man->setAlive(b, false);
}

void BulletSystem::onCollision_Bullet_Fighter(Entity* b)
{
	man->setAlive(b, false);
}

void BulletSystem::onRoundOver(bool pause)
{
	if (!pause) {
		for (auto e : man->getEntities(ecs::_grp_BULLETS)) {
			man->setAlive(e, false);
		}
	}

	active_ = false;
}

void BulletSystem::onRoundStart(bool pause)
{
	if (!pause) {
		for (auto e : man->getEntities(ecs::_grp_BULLETS)) {
			man->setAlive(e, false);
		}
	}
	active_ = true;
}
