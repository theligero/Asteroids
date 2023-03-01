#pragma once
#ifndef GAME_H_
#define GAME_H_

#include "../ecs/Manager.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/SoundEffect.h"

const int NUM_TEXTURES = 6;
const int NUM_SOUNDS = 1;

enum TextureName { ASTEROID, ASTEROID_GOLD, FIGHTER, FIGHTER2, FIRE, HEART };
enum SoundName {THRUST};

// estructura simple con una cadena de caracteres del archivo, y entero de final y columnas
typedef struct {
	std::string filename;
	int cols, rows;
} TextureDescription;

// array de TextureDescription con los datos de cada textura y si es spritesheet o no
const TextureDescription TEXT_DESCR[NUM_TEXTURES] = {
	{"asteroid.png", 6, 5},
	{"asteroid_gold.png", 6, 5},
	{"fighter.png", 1, 1},
	{"fighter2.png", 1, 1},
	{"fire.png", 1, 1},
	{"heart.png", 1, 1}
};

//const char* SOUND_DESCRIPTIONS[NUM_SOUNDS] = {
//	{"thrust.wav"}
//};

class Manager;

class Game {
public:
	Game();
	virtual ~Game();
	void run();
	void render();
	void update();
	void handleEvents();
private:
	SDL_Renderer* renderer;
	SDL_Window* window;
	std::unique_ptr<Texture> arrayTex[NUM_TEXTURES];
	Mix_Chunk* arraySound[NUM_SOUNDS];
	Mix_Chunk* chunk;
};

#endif GAME_H_