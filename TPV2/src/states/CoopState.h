#ifndef COOPSTATE_H_
#define COOPSTATE_H_

#include "GameState.h"
#include <SDL_net.h>
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../utils/Collisions.h"

const int MAX_CHARACTERS = 10;

class Game;

enum whichFighter { HOST, GUEST };

class CoopState : public GameState
{
private:
	Entity** fighter = new Entity*[2];
	char** username = new char*[2];
	whichFighter chosenFighter;
public:
	CoopState(Game* g);
	virtual ~CoopState();

	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	void checkCollision();
};

#endif /*COOPSTATE_H_*/