#ifndef ECS_DEF_H_
#define ECS_DEF_H_

#define SDLUTILS

//#define PARTE_2

#include <cstdint>

namespace ecs {
	using cmpId_type = uint8_t;

	enum cmpId : cmpId_type {
		TRANSFORM = 0,
		DEACCELERATION,
		IMAGE,
		HEALTH,
		FIGHTER_CTRL,
		GUN,
		SHOW_AT_OPPOSIDE_SIDE,
		FRAMED_IMAGE,
		GENERATIONS,
		FOLLOW,
		DISABLE_ON_EXIT,
		PAUSE_CTRL,
		// do not remove this
		LAST_CMP_ID
	};

	constexpr cmpId_type maxComponentId = LAST_CMP_ID;

	using grpId_type = uint8_t;
	enum grpId : grpId_type {
		_grp_GENERAL,
		_grp_ASTEROIDS,
		_grp_BULLETS,
		_grp_PAUSE,
		_LAST_GRP_ID
	};

	constexpr grpId_type maxGroupId = _LAST_GRP_ID;

	using hdlrId_type = uint8_t;
	enum hdlrId :hdlrId_type {
		_LAST_HDLR_ID
	};

	constexpr hdlrId_type maxHdlrId = _LAST_HDLR_ID;

	using sysId_type = uint8_t;
	enum sysId :sysId_type {
		_LAST_SYS_ID
	};

	constexpr sysId_type maxSystemId = _LAST_SYS_ID;
}

#endif /*ECS_DEF_H_*/