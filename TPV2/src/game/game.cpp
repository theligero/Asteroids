#include "Game.h"
#include "../components/Transform.h"
#include "../components/Image.h"
#include "../components/ShowAtOpposideSide.h"
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
	fighter->addComponent<Transform>(TRANSFORM, Vector2D(125, 125), Vector2D(- 0.0125, - 0.0125), 200, 300, 0);
	auto imageFighter = fighter->addComponent<Image>(IMAGE, arrayTex[FIGHTER].get());
	fighter->addComponent<ShowAtOpposideSide>(SHOW_AT_OPPOSIDE_SIDE, 800, 600);
}

void Game::render()
{
	SDL_RenderClear(renderer);
	Manager::instance()->render();
	SDL_RenderPresent(renderer);
}

void Game::update()
{
	Manager::instance()->update();
}

void Game::handleEvents()
{
}
