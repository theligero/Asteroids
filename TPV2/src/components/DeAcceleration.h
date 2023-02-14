#ifndef DEACCELERATION_H_
#define DEACCELERATION_H_

#include "../ecs/Component.h"
#include "Transform.h"

const float deAcceleration = 0.995;

class DeAcceleration : public Component
{
public:
	DeAcceleration() {}
	virtual ~DeAcceleration() {}

	void initComponent() override;
	void update() override;
private:
	Transform* tr;
};

#endif /*DEACCELERATION_H_*/