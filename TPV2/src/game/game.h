#ifndef GAME_H_
#define GAME_H_

class Game {
public:
	Game();
	virtual ~Game();
	void run();
	void render();
	void update();
	void handleEvents();
};

#endif GAME_H_