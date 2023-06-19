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
	void backToGame(Game* game) override;

private:
	grpId_type chooseWinLose(bool end);

	Entity* endText;
	Entity* infoText;
	Manager* man;
	bool win_;
};


#endif /*ENDSTATE_H_*/