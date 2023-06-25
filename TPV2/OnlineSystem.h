#ifndef ONLINE_SYSTEM_H_
#define ONLINE_SYSTEM_H_

#include "../ecs/System.h"
#include "../sdlutils/VirtualTimer.h"
//#include "../game/game.h"

class Game;
class SoundEffect;
class Transform;
class DeAcceleration;
class ShowAtOpposideSide;
class Gun;
class FighterCtrl;


class FighterSystem : public System {
public:
	FighterSystem(Game* g) : active_(true), game(g), fighter(nullptr), hitSound(nullptr) {}
	constexpr static ecs::sysId_type id = ecs::_sys_FIGHTER;
	// Reaccionar a los mensajes recibidos (llamando a métodos correspondientes).
	void receive(const Message& m) override;
	// Crear la entidad del caza, añadir sus componentes, asociarla con un handler
	// correspondiente, etc.
	void initSystem() override;
	// Si el juego está parado no hacer nada, en otro caso actualizar la velocidad
	// del caza y moverlo como en la práctica 1 (acelerar, desacelerar, etc). Además, 
	// si el juego no está parado y el jugador pulsa la tecla de disparo, enviar un
	// mensaje con las características físicas de la bala. Recuerda que se puede disparar
	// sólo una bala cada 0.25sec.
	void update() override;
	//Se encarga de mover el caza
	void fighterMovement();
	//Se encarga de procesar el input del jugador con respecto al caza
	void fighterInput();
	//Se encarga de realizar los disparos
	void fighterAttack();
	Entity* getFighter() {
		return fighter;
	}
private:
	// Para reaccionar al mensaje de que ha habido un choque entre el fighter y un
	// un asteroide. Poner el caza en el centro con velocidad (0,0) y rotación 0. No
	// hace falta desactivar la entidad (no dibujarla si el juego está parado).
	void onCollision_FighterAsteroid();
	// Para gestionar el mensaje de que ha acabado una ronda. Desactivar el sistema.
	void onRoundOver();
	// Para gestionar el mensaje de que ha empezado una ronda. Activar el sistema.
	void onRoundStart();
	// Indica si el sistema está activo o no (modificar el valor en onRoundOver y
	// onRoundStart, y en update no hacer nada si no está activo)
	bool active_;

	Game* game;
	Entity* fighter;
	SoundEffect* hitSound;

	Transform* tr;
	FighterCtrl* fc;
	DeAcceleration* da;
	ShowAtOpposideSide* saos;
	Gun* g;
};


#endif /*FIGHTER_SYSTEM_H_*/