#include "Game.h"
#include <iostream>

Game::Game()
{
#ifdef SDLUTILS
	SDLUtils::init("Asteroids v1.0", WINDOW_WIDTH, WINDOW_HEIGHT);
	window = sdlutils().window();
	renderer = sdlutils().renderer();
#else
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Asteroids v1.0", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	int mixOpenAudio = Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	assert(mixOpenAudio == 0);
	int mixInit_ret = Mix_Init(
		MIX_INIT_FLAC | MIX_INIT_MOD | MIX_INIT_MP3 | MIX_INIT_OGG);
	assert(mixInit_ret != 0);
	SoundEffect::setNumberofChannels(8); // we start with 8 channels
	int ttfInit_r = TTF_Init();
	assert(ttfInit_r == 0);
#endif

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	Font f("resources/fonts/ARIAL.ttf", 50);

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

	/*stateMachine = new GameStateMachine();
	stateMachine->changeState(new PlayState(this));*/
	mngr_ = Manager::instance();
	inputHdlr = InputHandler::instance();

	fighterSys = mngr_->addSystem<FighterSystem>(this);

	asteroidSys = mngr_->addSystem<AsteroidsSystem>(this);

	bulletSys = mngr_->addSystem<BulletSystem>();

	collisionSys = mngr_->addSystem<CollisionsSystem>();

	gameCtrlSys = mngr_->addSystem<GameCtrlSystem>(3);

	renderSys = mngr_->addSystem<RenderSystem>(this, 3);

	onlineSys = mngr_->addSystem<OnlineSystem>(this);
	
}

Game::~Game()
{
	Manager::close();
	for (auto& e : arrayTexture) {
		e.reset();
	}
	for (auto& e : arrayText) {
		e.reset();
	}
	for (auto& e : arraySound) {
		e.reset();
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit;
}

void Game::run()
{
	while (true) {
		//Sistemas update
		asteroidSys->update();
		bulletSys->update();
		collisionSys->update();
		fighterSys->update();
		gameCtrlSys->update();

		SDL_RenderClear(renderer);
		renderSys->update();
		SDL_RenderPresent(renderer);
		//refresh de singletons
		inputHdlr->refresh();
		mngr_->refresh();
		//Flush de mensajes
		mngr_->flushMessages();
	}
}

void Game::handleEvents()
{
}

