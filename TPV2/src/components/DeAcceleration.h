#ifndef DEACCELERATION_H_
#define DEACCELERATION_H_

#include "../ecs/Component.h"
#include "../sdlutils/VirtualTimer.h"
#include "Transform.h"



struct DeAcceleration : public Component
{
	const float deAcceleration = 0.9991;
public:
	constexpr static cmpId_type id = DEACCELERATION;
	DeAcceleration() : tr(nullptr) { };
	virtual ~DeAcceleration() { }
	void initComponent() override;
private:
	Transform* tr;
};

#endif /*DEACCELERATION_H_*/