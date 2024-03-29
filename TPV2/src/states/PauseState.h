#ifndef PAUSESTATE_H_
#define PAUSESTATE_H_

#include "GameState.h"
#include "PlayState.h"
#include <iostream>

class Game;
class Entity;

class PauseState : public GameState
{
public:
	PauseState(Game* g);
	PauseState(Game* g, std::string message) : PauseState(g) { std::cout << message << std::endl; }

	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();
	static void backToGame(Game* game);

private:
	Entity* pauseText;
};

#endif /*MAINMENUSTATE_H_*/
