#ifndef PLAYSTATE_H_
#define PLAYSTATE_H_

#include "GameState.h"
#include "PauseState.h"
#include "../game/game.h"
#include "../game/AsteroidsManager.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/SoundEffect.h"
#include "../sdlutils/Font.h"
#include "../components/Transform.h"
#include "../components/Image.h"
#include "../components/ShowAtOpposideSide.h"
#include "../components/FighterCtrl.h"
#include "../components/Health.h"
#include "../components/DeAcceleration.h"
#include "../components/DisableOnExit.h"
#include "../components/FramedImage.h"
#include "../components/Gun.h"
#include "../components/Follow.h"
#include <iostream>


class PlayState : public GameState
{
public:
	PlayState(Game* g);
	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	void checkCollision();

	void enterPause();
private:
	AsteroidsManager* asteroidManager = nullptr;
};

#endif /*PLAYSTATE_H_*/