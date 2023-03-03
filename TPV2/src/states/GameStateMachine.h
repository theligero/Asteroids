#ifndef GAMESTATEMACHINE_H_
#define GAMESTATEMACHINE_H_

#include <stack>
#include "GameState.h"

class GameState;

class GameStateMachine
{
private:
	// pila de estados de juego
	std::stack<GameState*> gameStack;
public:
	// estado actual del juego
	GameState* currentState();
	// añadido de un nuevo estado
	void pushState(GameState* state);
	// cambio por un nuevo estado
	void changeState(GameState* state);
	// eliminación del actual estado
	void popState();
	// actualizado
	void update();
	// renderizado
	void render();
};

#endif /*GAMESTATEMACHINE_H_*/