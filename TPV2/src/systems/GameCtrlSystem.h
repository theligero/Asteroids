#ifndef GAME_CTRL_SYSTEM_H_
#define GAME_CTRL_SYSTEM_H_

#include "../ecs/System.h"
#include <SDL_stdinc.h>

class Health;

class GameCtrlSystem : public System {
public:
	GameCtrlSystem(int initialState) : infoText(nullptr), winText(nullptr), loseText(nullptr), winner_(0), state_(initialState), fighter(nullptr) {}
	constexpr static ecs::sysId_type id = ecs::_sys_GAME_CTRL;
	// Reaccionar a los mensajes recibidos (llamando a m�todos correspondientes).
	void receive(const Message& m) override;
	// Inicializar el sistema, etc.
	void initSystem() override;
	// Si el juego no est� parado y el jugador pulsa SDLK_SPACE cambia el estado
	// como en la pr�ctica 1, etc. Tiene que enviar mensajes correspondientes cuando
	// empieza una ronda o cuando empieza una nueva partida.
	void update() override;
private:
	// Para gestionar el mensaje de que ha habido un choque entre el fighterSolo y un
	// un asteroide. Tiene que avisar que ha acabado la ronda, quitar una vida
	// al fighterSolo, y si no hay m�s vidas avisar que ha acabado el juego (y quien
	// es el ganador).
	void onCollision_FighterAsteroid(Health* ftrHealth);
	// Para gestionar el mensaje de que no hay m�s asteroides. Tiene que avisar que
	// ha acabado la ronda y adem�s que ha acabado el juego (y quien es el ganador)
	void onAsteroidsExtinction();
	void onFighterBulletDeath();
	Uint8 winner_; // 0 - None, 1 - Asteroid, 2- Fighter
	Uint8 state_; // 0 - Play, 1 - Pause, 2 - End, 3 - Main Menu, 4 - Coop

	Entity* infoText;
	Entity* winText;
	Entity* loseText;
	Entity* fighter;
	Entity* title = nullptr;
	Entity* jugarSolo = nullptr;
	Entity* jugarCoop = nullptr;
	int mouseX = 0;
	int mouseY = 0;
};

#endif /*GAME_CTRL_SYSTEM_H_*/