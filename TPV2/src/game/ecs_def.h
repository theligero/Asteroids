#ifndef ECS_DEF_H_
#define ECS_DEF_H_

#define SDLUTILS

#include <cstdint>

namespace ecs {
	using cmpId_type = uint8_t;

	enum cmpId : cmpId_type {
		TRANSFORM = 0,
		DEACCELERATION,
		HEALTH,
		FIGHTER_CTRL,
		GUN,
		SHOW_AT_OPPOSIDE_SIDE,
		FRAMED_IMAGE,
		GENERATIONS,
		FOLLOW,
		DISABLE_ON_EXIT,
		PAUSE_CTRL,
		CLICKABLE,
		// do not remove this
		LAST_CMP_ID
	};

	constexpr cmpId_type maxComponentId = LAST_CMP_ID;

	using grpId_type = uint8_t;
	enum grpId : grpId_type {
		_grp_GENERAL,
		_grp_FIGHTER,
		_grp_ASTEROIDS,
		_grp_BULLETS,
		_grp_INFO,
		_grp_WIN,
		_grp_LOSE,
		_grp_TITLE,
		_grp_COOP_BUTTON,
		_grp_SOLO_BUTTON,
		_grp_COOP_FIGHTERS,
		_LAST_GRP_ID
	};

	constexpr grpId_type maxGroupId = _LAST_GRP_ID;

	using sysId_type = uint8_t;
	enum sysId : sysId_type {
		_sys_ASTEROIDS = 0,
		_sys_COLLISIONS,
		_sys_BULLET,
		_sys_FIGHTER,
		_sys_GAME_CTRL,
		_sys_RENDER,
		_sys_ONLINE,

		// do not remove this
		_LAST_SYS_ID
	};
	constexpr sysId_type maxSystemId = _LAST_SYS_ID;

	using msgId_type = uint8_t;
	enum msgId : msgId_type {
		_m_PAUSE_GAME,
		_m_START_GAME,
		_m_MAIN_MENU,
		_m_END_GAME,
		_m_FIGHTER_HIT,
		_m_BULLET_SHOT,
		_m_ASTEROID_DESTROYED,
		_m_FIGHTER_BULLET_HIT,
		_m_MOVE_ENEMY,
		_m_ENEMY_DEAD,
		_m_NO_MORE_ASTEROIDS,
		_m_IS_HOST,
		_m_IS_GUEST
	};
}

#endif /*ECS_DEF_H_*/