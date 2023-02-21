#ifndef DEACCELERATION_H_
#define DEACCELERATION_H_

#include "../ecs/Component.h"
#include "../sdlutils/VirtualTimer.h"
#include "Transform.h"

const float deAcceleration = 0.9995;

class DeAcceleration : public Component
{
public:
	DeAcceleration() { timer = new VirtualTimer(); lastTime = timer->currTime(); }
	virtual ~DeAcceleration() { delete timer; }

	void initComponent() override;
	void update() override;
private:
	Transform* tr;
	VirtualTimer* timer;
	Uint32 lastTime;
};

#endif /*DEACCELERATION_H_*/