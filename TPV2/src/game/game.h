#ifndef GAME_H_
#define GAME_H_

#include "../ecs/Manager.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/SoundEffect.h"
#include "../sdlutils/Font.h"
#include "../components/Transform.h"
#include "../components/Image.h"
#include "../components/ShowAtOpposideSide.h"
#include "../components/FighterCtrl.h"
#include "../components/Health.h"
#include "../components/DeAcceleration.h"
#include "../components/DisableOnExit.h"
#include "../components/FramedImage.h"
#include "../components/Gun.h"
#include "../components/Follow.h"
#include "../states/GameStateMachine.h"
#include "../states/PlayState.h"

const int NUM_TEXTURES = 6;
const int NUM_TEXTS = 1;
const int NUM_SOUNDS = 4;

enum TextureName { ASTEROID, ASTEROID_GOLD, FIGHTER, FIGHTER2, FIRE, HEART};
enum TextName { PAUSE };
enum SoundName { THRUST, SHOOT, FIGHTER_EXPLOSION, ASTEROID_EXPLOSION };

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

// estructura simple con una cadena de caracteres del archivo, y entero de final y columnas
typedef struct {
	std::string filename;
	int cols, rows;
} TextureDescription;

typedef struct {
	std::string text;
	SDL_Color fgColor;
	SDL_Color bgColor;
} TextDescription;

// array de TextureDescription con los datos de cada textura y si es spritesheet o no
const TextureDescription TEXTURE_DESCR[NUM_TEXTURES] = {
	{"asteroid.png", 6, 5},
	{"asteroid_gold.png", 6, 5},
	{"fighter.png", 1, 1},
	{"fighter2.png", 1, 1},
	{"fire.png", 1, 1},
	{"heart.png", 1, 1},
};

const TextDescription TEXT_DESCRIP[NUM_TEXTS] = {
	{"PAUSE", build_sdlcolor(0x112233ff), build_sdlcolor(0xffffffff)}
};

const std::string SOUND_DESCR[NUM_SOUNDS] = {
	{"thrust.wav"},
	{"fire.wav"},
	{"explosion.wav"},
	{"explosion1.wav"}
};

class Manager;

class Game {
public:
	Game();
	virtual ~Game();
	void run();
	void render();
	void update();
	void handleEvents();
	Texture* getArrayTexture(TextureName key) { return arrayTexture[key].get(); }
	Texture* getArrayText(TextName key) { return arrayText[key].get(); }
	SoundEffect* getArraySound(SoundName key) { return arraySound[key].get(); }
	GameStateMachine* getStateMachine();
	

	
private:
	SDL_Renderer* renderer;
	SDL_Window* window;
	std::unique_ptr<Texture> arrayTexture[NUM_TEXTURES];
	std::unique_ptr<Texture> arrayText[NUM_TEXTS];
	std::unique_ptr<SoundEffect> arraySound[NUM_SOUNDS];
	GameStateMachine* stateMachine = nullptr;
};

#endif GAME_H_