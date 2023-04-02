#ifndef RENDER_SYSTEM_H_
#define RENDER_SYSTEM_H_

#include "../ecs/System.h"
#include <SDL_stdinc.h>

class RenderSystem : public System {
public:
	// Reaccionar a los mensajes recibidos (llamando a m�todos correspondientes).
	void receive(const Message& m) override;
	// Inicializar el sistema, etc.
	void initSystem() override;
	// - Dibujar asteroides, balas y caza (s�lo si el juego no est� parado).
	// - Dibujar las vidas (siempre).
	// - Dibujar los mensajes correspondientes: si el juego est� parado, etc (como en
	// la pr�ctica 1)
	void update() override;
private:
	// Para gestionar los mensajes correspondientes y actualizar los atributos
	// winner_ y state_. 
	void onRoundStart();
	void onRoundOver();
	void onGameStart();
	void onGameOver();
	Uint8 winner_; // 0 - None, 1 - Asteroid, 2- Fighter
	Uint8 state_; // El estado actual de juego (como en GameCtrlSystem)
};

#endif /*RENDER_SYSTEM_H_*/