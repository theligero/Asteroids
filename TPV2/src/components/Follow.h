#ifndef FOLLOW_H_
#define FOLLOW_H_

#include "../ecs/Component.h"
#include "Transform.h"
#include <assert.h>

class Follow : public Component
{
public:
	constexpr static cmpId_type id = ecs::FOLLOW;
	Follow(Entity* followed) : followedEntity(followed) { }
	virtual ~Follow() { }

	void initComponent() override;
	void update() override;
private:
	Entity* followedEntity;
	Transform* followedTr;
	Transform* tr;
};

#endif /*FOLLOW_H_*/