#ifndef GUN_H_
#define GUN_H_

#include "../ecs/Component.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SoundEffect.h"
#include "../sdlutils/VirtualTimer.h"
#include "Transform.h"

class Gun : public Component
{
public:
	Gun(SoundEffect* soundHandle) : shootSound(soundHandle), tr(nullptr){ clock = new VirtualTimer(); }
	virtual ~Gun() {}
	void initComponent() override;
	void update() override;
private:
	Transform* tr;
	Uint32 lastTime = 0;
	SoundEffect* shootSound;
	VirtualTimer* clock;
};

#endif /*GUN_H_*/