#ifndef GUN_H_
#define GUN_H_

#include "../ecs/Component.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SoundEffect.h"
#include "../sdlutils/VirtualTimer.h"
#include "../sdlutils/Texture.h"
#include "Transform.h"
#include "DisableOnExit.h"
#include "../ecs/Manager.h"


struct Gun : public Component
{
public:
	constexpr static cmpId_type id = ecs::GUN;
	Gun(SoundEffect* soundHandle, int w, int h) : 
		WindowWidth(w), WindowHeight(h), shootSound(soundHandle), 
		 tr(nullptr) { clock = new VirtualTimer(); }
	virtual ~Gun() {}
	inline SoundEffect* getSound() { return shootSound; }
	inline Uint32 getLastTime() { return lastTime; }
	inline VirtualTimer* getClock() { return clock; }
	inline int getWindowWidth() { return WindowWidth; }
	inline int getWindowHeight() { return WindowHeight; }
	void initComponent() override;
private:
	Transform* tr;
	Uint32 lastTime = 0;
	SoundEffect* shootSound;
	VirtualTimer* clock;
	int WindowWidth;
	int WindowHeight;
};

#endif /*GUN_H_*/