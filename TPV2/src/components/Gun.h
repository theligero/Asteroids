#ifndef GUN_H_
#define GUN_H_

#include "../ecs/Component.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SoundEffect.h"
#include "../sdlutils/VirtualTimer.h"
#include "../sdlutils/Texture.h"
#include "Transform.h"
#include "Image.h"
#include "DisableOnExit.h"
#include "../ecs/Manager.h"


class Gun : public Component
{
public:
	Gun(SoundEffect* soundHandle, Texture* t, int w, int h) : WindowWidth(w), WindowHeight(h), shootSound(soundHandle), bulletTexture(t), tr(nullptr) { clock = new VirtualTimer(); }
	virtual ~Gun() {}
	void initComponent() override;
	void update() override;
private:
	Transform* tr;
	Texture* bulletTexture;
	Uint32 lastTime = 0;
	SoundEffect* shootSound;
	VirtualTimer* clock;
	int WindowWidth;
	int WindowHeight;
};

#endif /*GUN_H_*/