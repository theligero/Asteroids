#ifndef MAINMENUSTATE_H_
#define MAINMENUSTATE_H_

#include "GameState.h"
#include "PlayState.h"
#include "CoopState.h"
#include "../game/game.h"

class Game;

class MainMenuState : public GameState
{
private:
	int mouseX = 0;
	int mouseY = 0;

public:
	
	MainMenuState(Game* g);
	virtual ~MainMenuState() {}

	virtual void update();
	virtual void render();
	virtual void handleEvent();

	virtual bool onEnter();
	virtual bool onExit();

	static void beginSoloGame(Game* game);
	static void beginCoopGame(Game* game);
	static void endGame(Game* game);
	static void loadGame(Game* game);
private:
	Entity* jugarSolo = nullptr;
	Entity* jugarCoop = nullptr;
	};

#endif /*MAINMENUSTATE_H_*/