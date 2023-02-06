#include "Game.h"
#include "../components/Transform.h"
#include "../components/Image.h"

Game::Game() : manager(nullptr)
{
	window = SDL_CreateWindow("Asteroids v1.0", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

Game::~Game()
{
	delete manager;
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit;
}

void Game::run()
{
	manager = new Manager();

	auto fighter = manager->addEntity();
	auto asteroid = manager->addEntity();
	fighter->addComponent<Transform>(TRANSFORM, Vector2D(250, 250), Vector2D(), 200, 300, 400);
	// auto imageFighter = fighter->addComponent<Image>(IMAGE, Texture(renderer, "fighter.png"));
	// auto imagenIm = imagen->addComponent<Image>(IMAGE);
}

void Game::render()
{
	manager->render();
}

void Game::update()
{
	manager->update();
}

void Game::handleEvents()
{
}
