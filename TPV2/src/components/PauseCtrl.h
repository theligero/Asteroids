#ifndef PAUSE_CTRL_H_
#define PAUSE_CTRL_H_

#include "../ecs/Component.h"
#include "../game/game.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SoundEffect.h"
#include "../states/PlayState.h"


class PauseCtrl : public Component
{
public:
	PauseCtrl(Game* g, bool pause = true) : tr(nullptr), game(g), isPaused(pause) { InputHandler::instance(); }
	virtual ~PauseCtrl() { InputHandler::close(); }

	void initComponent() override;
	void update() override;
private:
	Transform* tr;
	Game* game;
	bool isPaused;
};

#endif /*PAUSE_CTRL_H_*/