#ifndef GAMESTATE_H_
#define GAMESTATE_H_

#include "list"

class Game;

class GameState
{
protected:
	Game* game = nullptr;
public:
	virtual void update() = 0;
	virtual void render() = 0;

	virtual bool onEnter() = 0;
	virtual bool onExit() = 0;

	virtual void backToGame(Game* game) {};
};

#endif /*GAMESTATE_H_*/