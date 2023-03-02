#ifndef FIGHTER_CTRL_H_
#define FIGHTER_CTRL_H_

#include "../ecs/Component.h"
#include "../sdlutils/InputHandler.h"
#include "Transform.h"
#include "../sdlutils/SoundEffect.h"

class FighterCtrl : public Component
{
public:
	FighterCtrl(SoundEffect* soundHandle) : tr(nullptr), thrustSound(soundHandle) { InputHandler::init(); }
	virtual ~FighterCtrl() { InputHandler::close(); }

	void initComponent() override;
	void update() override;
private:
	Transform* tr;
	SoundEffect* thrustSound;
};

#endif /*FIGHTER_CTRL_H_*/