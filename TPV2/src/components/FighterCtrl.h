#ifndef FIGHTER_CTRL_H_
#define FIGHTER_CTRL_H_

#include "Transform.h"
#include "Gun.h"
#include "../ecs/Component.h"
#include "../game/game.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SoundEffect.h"

class Game;

struct FighterCtrl : public Component
{
	const float thrust = 0.2f;
	const float speed_Limit = 3.0f;
public:
	constexpr static cmpId_type id = ecs::FIGHTER_CTRL;
	FighterCtrl(SoundEffect* soundHandle, Game* g) : tr(nullptr), thrustSound(soundHandle), game(g), gun(nullptr) { InputHandler::instance(); }
	virtual ~FighterCtrl() { InputHandler::close(); }
	inline SoundEffect* getSound() { return thrustSound; }
	void initComponent() override;
private:
	Transform* tr;
	Gun* gun;
	Game* game;
	SoundEffect* thrustSound;
};

#endif /*FIGHTER_CTRL_H_*/