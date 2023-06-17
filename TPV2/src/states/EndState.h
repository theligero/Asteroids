#ifndef ENDSTATE_H_
#define ENDSTATE_H_

#include "GameState.h"
#include "../ecs/Manager.h"
#include <iostream>

class Game;
class Entity;

class EndState : public GameState
{
public:
	EndState(Game* g, bool win);

	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();
	static void backToMenu(Game* game);

private:
	Entity* endText;
	Manager* man;
};


#endif /*ENDSTATE_H_*/