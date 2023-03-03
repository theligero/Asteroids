#ifndef MAINMENUSTATE_H_
#define MAINMENUSTATE_H_

#include "GameState.h"
#include "PlayState.h"
#include "MenuButton.h"
#include "Game.h"
#include "FileNotFoundError.h"

class Game;

class MainMenuState : public GameState
{

public:
	
	MainMenuState(Game* g);
	virtual ~MainMenuState();

	virtual void update();
	virtual void render();
	virtual void handleEvent();

	virtual bool onEnter();
	virtual bool onExit();

	static void beginGame(Game* game);
	static void endGame(Game* game);
	static void loadGame(Game* game);
private:
	
	};

#endif /*MAINMENUSTATE_H_*/