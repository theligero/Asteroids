#include "Game.h"
#include "../components/Transform.h"
#include "../components/Image.h"
#include "../components/ShowAtOpposideSide.h"
#include "../components/FighterCtrl.h"
#include "../components/DeAcceleration.h"
#include "../components/DisableOnExit.h"
#include "../components/FramedImage.h"
#include "../sdlutils/Font.h"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

Game::Game()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Asteroids v1.0", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
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
	for (auto& e : arrayTex) {
		e.reset();
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit;
}

void Game::run()
{
	// crear manager
	auto& man = *Manager::instance();
	
	auto fighter = man.addEntity();
	fighter->addComponent<Transform>(TRANSFORM, Vector2D(125, 125), Vector2D(-0.0125, -0.0125), 35, 30, 0);
	fighter->addComponent<Image>(IMAGE, arrayTex[FIGHTER].get());
	fighter->addComponent<ShowAtOpposideSide>(SHOW_AT_OPPOSIDE_SIDE, WINDOW_WIDTH, WINDOW_HEIGHT);
	fighter->addComponent<FighterCtrl>(FIGHTER_CTRL);
	fighter->addComponent<DeAcceleration>(DEACCELERATION);

	auto asteroid = man.addEntity();
	asteroid->addComponent<Transform>(TRANSFORM, Vector2D(250, 250), Vector2D(0, 0), 25, 25, 0);
	asteroid->addComponent<FramedImage>(IMAGE, arrayTex[ASTEROID].get(), TEXT_DESCR[ASTEROID].rows, TEXT_DESCR[ASTEROID].cols);
	// fighter->addComponent<DisableOnExit>(DISABLE_ON_EXIT, WINDOW_WIDTH, WINDOW_HEIGHT);
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
