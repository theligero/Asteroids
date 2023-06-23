#ifndef FOLLOW_H_
#define FOLLOW_H_

#include "../ecs/Component.h"
#include "Transform.h"
#include <assert.h>

#ifdef SDLUTILS
const float FOLLOWING_SPEED = 1.0f;
#else
const float FOLLOWING_SPEED = 0.01f;
#endif
const int UPDATE_STEP = 300;

class Follow : public Component
{
public:
	constexpr static cmpId_type id = ecs::FOLLOW;
	Follow(Entity* followed) : followedEntity(followed) { }
	virtual ~Follow() { }
	inline Transform* getFollowed() { return followedTr; }
	void initComponent() override;
private:
	Entity* followedEntity;
	Transform* followedTr;
	Transform* tr;
};

#endif /*FOLLOW_H_*/