#ifndef PAUSESTATE_H_
#define PAUSESTATE_H_

#include "GameState.h"
#include "PlayState.h"


class Game;

class PauseState : public GameState
{
public:
	PauseState(Game* g);

	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();
	static void backToGame(Game* game);

private:

};

#endif /*MAINMENUSTATE_H_*/
