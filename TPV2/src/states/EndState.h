#ifndef ENDSTATE_H_
#define ENDSTATE_H_

#include "GameState.h"

class EndState : public GameState
{
private:
	
public:
	EndState(Game* g);
	virtual ~EndState();

	virtual void update();
	virtual void render();
	virtual void handleEvent();

	virtual bool onEnter();
	virtual bool onExit();

	static void goToMenu(Game* game);
};

#endif /*ENDSTATE_H_*/