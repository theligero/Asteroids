#ifndef COOPSTATE_H_
#define COOPSTATE_H_

#include "GameState.h"
#include <SDL_net.h>

class Game;

class CoopState : public GameState
{
private:
	// TCPsocket a;
public:
	CoopState(Game* g);
	virtual ~CoopState();

	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();
};

#endif /*COOPSTATE_H_*/