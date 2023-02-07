#include "Game.h"
#include "../components/Transform.h"
#include "../components/Image.h"

Game::Game() : manager(nullptr)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Asteroids v1.0", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	for (int i = 0; i < NUM_TEXTURES; ++i) {
		const TextureDescription& desc = TEXT_DESCR[i];
		arrayTex[i] = new Texture(renderer, "resources/images/" + desc.filename);
	}
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
	fighter->addComponent<Transform>(TRANSFORM, Vector2D(250, 250), Vector2D(0, 0), 200, 300, 400);
	auto imageFighter = fighter->addComponent<Image>(IMAGE, arrayTex[FIGHTER]);
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
