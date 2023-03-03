#pragma once
#ifndef GAME_H_
#define GAME_H_

#include "../ecs/Manager.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/SoundEffect.h"
#include "../sdlutils/Font.h"

const int NUM_TEXTURES = 6;
const int NUM_TEXTS = 1;
const int NUM_SOUNDS = 2;

enum TextureName { ASTEROID, ASTEROID_GOLD, FIGHTER, FIGHTER2, FIRE, HEART};
enum TextName { PAUSE };
enum SoundName {THRUST, SHOOT};

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
	{"fire.wav"}
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
	bool checkCollision();
	
private:
	SDL_Renderer* renderer;
	SDL_Window* window;
	std::unique_ptr<Texture> arrayTexture[NUM_TEXTURES];
	std::unique_ptr<Texture> arrayText[NUM_TEXTS];
	std::unique_ptr<SoundEffect> arraySound[NUM_SOUNDS];
};

#endif GAME_H_