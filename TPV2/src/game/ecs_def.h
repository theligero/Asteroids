#ifndef ECS_DEF_H_
#define ECS_DEF_H_

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
		// do not remove this
		LAST_CMP_ID
	};

	constexpr cmpId_type maxComponentId = LAST_CMP_ID;
}

#endif /*ECS_DEF_H_*/