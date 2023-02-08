#include "Game.h"
#include "../components/Transform.h"
#include "../components/Image.h"
#include "../sdlutils/Font.h"

Game::Game()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Asteroids v1.0", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	for (int i = 0; i < NUM_TEXTURES; ++i) {
		const TextureDescription& desc = TEXT_DESCR[i];
		arrayTex[i] = std::make_unique<Texture>(renderer, "resources/images/" + desc.filename);
	}
}

Game::~Game()
{
	Manager::close();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit;
}

void Game::run()
{
	// crear manager
	Manager::init();
	
	auto fighter = Manager::instance()->addEntity();
	auto asteroid = Manager::instance()->addEntity();
	fighter->addComponent<Transform>(TRANSFORM, Vector2D(250, 250), Vector2D(0, 0), 200, 300, 400);
	auto imageFighter = fighter->addComponent<Image>(IMAGE, arrayTex[FIGHTER].get());
}

void Game::render()
{
	Manager::instance()->render();
}

void Game::update()
{
	Manager::instance()->update();
}

void Game::handleEvents()
{
}
