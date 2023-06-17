#ifndef FIGHTER_CTRL_H_
#define FIGHTER_CTRL_H_

#include "Transform.h"
#include "Gun.h"
#include "../ecs/Component.h"
#include "../game/game.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SoundEffect.h"
#include "../states/PauseState.h"


class FighterCtrl : public Component
{
public:
	constexpr static cmpId_type id = ecs::FIGHTER_CTRL;
	FighterCtrl(SoundEffect* soundHandle, Game* g) : tr(nullptr), thrustSound(soundHandle), game(g) { InputHandler::instance(); }
	virtual ~FighterCtrl() { InputHandler::close(); }

	void initComponent() override;
	void update() override;
private:
	Transform* tr;
	Gun* gun;
	Game* game;
	SoundEffect* thrustSound;
};

#endif /*FIGHTER_CTRL_H_*/