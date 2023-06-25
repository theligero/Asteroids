#ifndef RENDER_SYSTEM_H_
#define RENDER_SYSTEM_H_

#include "../ecs/System.h"
#include "../components/Transform.h"
#include "../sdlutils/Texture.h"

class Game;


class RenderSystem : public System {
public:
	RenderSystem(Game* g, int initialState) : game(g), fighterTex(nullptr), bulletTex(nullptr), lifeTex(nullptr), infoText(nullptr), loseText(nullptr), winText(nullptr), winner_(0), state_(initialState) {};
	constexpr static ecs::sysId_type id = ecs::_sys_RENDER;
	// Reaccionar a los mensajes recibidos (llamando a métodos correspondientes).
	void receive(const Message& m) override;
	// Inicializar el sistema, etc.
	void initSystem() override;
	// - Dibujar asteroides, balas y caza (sólo si el juego no está parado).
	// - Dibujar las vidas (siempre).
	// - Dibujar los mensajes correspondientes: si el juego está parado, etc (como en
	// la práctica 1)
	void update() override;
private:
	SDL_Rect getTrRect(Transform* tr);
	SDL_Rect getTrRect(Vector2D pos, Transform* tr);
	// Para gestionar los mensajes correspondientes y actualizar los atributos
	// winner_ y state_. 
	//El juego está en el menú principal y termina online
	void onMainMenu();
	//EL juego esta en online
	void onOnline();
	//Pausa el juego. PAUSE
	void onRoundOver();
	//Empieza el juego de cero o se vuelve después de pausar START
	void onGameStart();
	//Se acaba el juego, pierdes o ganas. END
	void onGameOver(bool win);
	Uint8 winner_; // 0 - None, 1 - Asteroid, 2- Fighter
	Uint8 state_; // 0 - Play, 1 - Pause, 2 - End, 3 - Main Menu, 4 - Coop

	Game* game;
	Texture* fighterTex;
	Texture* bulletTex;
	Texture* lifeTex;
	Texture* infoText;
	Texture* loseText;
	Texture* winText;
	Texture* soloText;
	Texture* coopText;
	Texture* titleText;

};

#endif /*RENDER_SYSTEM_H_*/