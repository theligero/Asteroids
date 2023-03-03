#include "Game.h"
#include "../components/Transform.h"
#include "../components/Image.h"
#include "../components/ShowAtOpposideSide.h"
#include "../components/FighterCtrl.h"
#include "../components/Health.h"
#include "../sdlutils/Font.h"
#include "../components/DeAcceleration.h"
#include "../components/DisableOnExit.h"
#include "../components/FramedImage.h"
#include "../components/Gun.h"
#include "../components/Follow.h"
#include <iostream>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

Game::Game()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Asteroids v1.0", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	int mixOpenAudio = Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	assert(mixOpenAudio == 0);
	int mixInit_ret = Mix_Init(
		MIX_INIT_FLAC | MIX_INIT_MOD | MIX_INIT_MP3 | MIX_INIT_OGG);
	assert(mixInit_ret != 0);
	SoundEffect::setNumberofChannels(8); // we start with 8 channels
	int ttfInit_r = TTF_Init();
	assert(ttfInit_r == 0);
	Font f("resources/fonts/ARIAL.ttf", 18);
	for (int i = 0; i < NUM_TEXTURES; ++i) {
		const TextureDescription& textureDesc = TEXTURE_DESCR[i];
		arrayTexture[i] = std::make_unique<Texture>(renderer, "resources/images/" + textureDesc.filename);
	}
	for (int i = 0; i < NUM_TEXTS; ++i) {
		const TextDescription& textDesc = TEXT_DESCRIP[i];
		arrayText[i] = std::make_unique<Texture>(renderer, textDesc.text, f, textDesc.fgColor, textDesc.bgColor);
	}
	for (int i = 0; i < NUM_SOUNDS; ++i) {
		const std::string soundDesc = SOUND_DESCR[i];
		arraySound[i] = std::make_unique<SoundEffect>("resources/sound/" + soundDesc);
	}
}

Game::~Game()
{
	Manager::close();
	for (auto& e : arrayTexture) {
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
	fighter->addComponent<Transform>(TRANSFORM, Vector2D(400, 300), Vector2D(0, 0), 35, 30, 0);
	fighter->addComponent<DeAcceleration>(DEACCELERATION);
	fighter->addComponent<Health>(HEALTH, WINDOW_WIDTH, WINDOW_HEIGHT, arrayTexture[HEART].get());
	fighter->addComponent<Image>(IMAGE, arrayText[PAUSE].get());
	fighter->addComponent<FighterCtrl>(FIGHTER_CTRL, arraySound[THRUST].get());
	fighter->addComponent<ShowAtOpposideSide>(SHOW_AT_OPPOSIDE_SIDE, WINDOW_WIDTH, WINDOW_HEIGHT);
	fighter->addComponent<Gun>(GUN, arraySound[SHOOT].get(), arrayTexture[FIRE].get(), WINDOW_WIDTH, WINDOW_HEIGHT);
	fighter->getComponent<Transform>(TRANSFORM)->getPos();
	

	auto asteroid = man.addEntity(_grp_ASTEROIDS);
	asteroid->addComponent<Transform>(TRANSFORM, Vector2D(250, 250), Vector2D(0, 0), 25, 25, 0);
	asteroid->addComponent<ShowAtOpposideSide>(SHOW_AT_OPPOSIDE_SIDE, WINDOW_WIDTH, WINDOW_HEIGHT);
	asteroid->addComponent<FramedImage>(IMAGE, arrayTexture[ASTEROID].get(), TEXTURE_DESCR[ASTEROID].rows, TEXTURE_DESCR[ASTEROID].cols);
	asteroid->addComponent<Follow>(FOLLOW, fighter);
	//asteroid->addComponent<DisableOnExit>(DISABLE_ON_EXIT, WINDOW_WIDTH, WINDOW_HEIGHT);
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
	InputHandler::instance()->refresh();
}

void Game::handleEvents()
{
}
