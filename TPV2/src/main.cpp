#include <iostream>
#include "game/game.h"

int main(int ac, char **av) {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	Game game;
	game.run();
	game.render();
	game.update();

	return 0;
}

