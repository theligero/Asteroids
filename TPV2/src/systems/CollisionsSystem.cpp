#include "CollisionsSystem.h"
#include "../ecs/Manager.h"

void CollisionsSystem::receive(const Message& m)
{
	switch (m.id) {
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
}

void CollisionsSystem::update()
{
	if (active_) {

	}
}

void CollisionsSystem::onRoundOver()
{
	active_ = false;
}

void CollisionsSystem::onRoundStart()
{
	active_ = true;
}
