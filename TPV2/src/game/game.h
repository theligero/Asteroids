#ifndef GAME_H_
#define GAME_H_

#include "../ecs/Manager.h"
#include <SDL.h>

class Manager;

class Game {
public:
	Game();
	virtual ~Game();
	void run();
	void render();
	void update();
	void handleEvents();
private:
	Manager* manager;
	SDL_Renderer* renderer;
	SDL_Window* window;
};

#endif GAME_H_