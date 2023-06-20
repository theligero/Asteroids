#ifndef GAME_CTRL_SYSTEM_H_
#define GAME_CTRL_SYSTEM_H_

#include "../ecs/System.h"
#include <SDL_stdinc.h>

class Health;

class GameCtrlSystem : public System {
public:
	GameCtrlSystem() : infoText(nullptr), winText(nullptr), loseText(nullptr), winner_(0), state_(0) {}
	constexpr static ecs::sysId_type id = ecs::_sys_GAME_CTRL;
	// Reaccionar a los mensajes recibidos (llamando a métodos correspondientes).
	void receive(const Message& m) override;
	// Inicializar el sistema, etc.
	void initSystem() override;
	// Si el juego no está parado y el jugador pulsa SDLK_SPACE cambia el estado
	// como en la práctica 1, etc. Tiene que enviar mensajes correspondientes cuando
	// empieza una ronda o cuando empieza una nueva partida.
	void update() override;
private:
	// Para gestionar el mensaje de que ha habido un choque entre el fighter y un
	// un asteroide. Tiene que avisar que ha acabado la ronda, quitar una vida
	// al fighter, y si no hay más vidas avisar que ha acabado el juego (y quien
	// es el ganador).
	void onCollision_FighterAsteroid(Health* ftrHealth);
	// Para gestionar el mensaje de que no hay más asteroides. Tiene que avisar que
	// ha acabado la ronda y además que ha acabado el juego (y quien es el ganador)
	void onAsteroidsExtinction();
	Uint8 winner_; // 0 - None, 1 - Asteroid, 2- Fighter
	Uint8 state_; // 0 - Play, 1 - Pause, 2 - End

	Entity* infoText;
	Entity* winText;
	Entity* loseText;
};

#endif /*GAME_CTRL_SYSTEM_H_*/