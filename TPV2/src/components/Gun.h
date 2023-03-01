#ifndef GUN_H_
#define GUN_H_

#include "../ecs/Component.h"
#include "../sdlutils/SDLUtils.h"
#include "Transform.h"

class Gun : public Component
{
public:
	Gun() {}
	virtual ~Gun() {}
	void initComponent() override;
	void update() override;
private:
	Transform* tr;
	Uint32 lastTime = 0;
};

#endif /*GUN_H_*/