#ifndef FIGHTER_SYSTEM_H_
#define FIGHTER_SYSTEM_H_

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
	FighterSystem(Game* g) : active_(true), game(g), fighterSolo(nullptr), hitSound(nullptr) {}
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
	void fighterMovement(Transform *tr, ShowAtOpposideSide *saos, DeAcceleration* da);
	//Se encarga de procesar el input del jugador con respecto al caza
	void fighterInput(Transform* tr, FighterCtrl* fc);
	//Se encarga de realizar los disparos
	void fighterAttack(Transform* tr, Gun* g);
	//Se encarga de realizar los disparos y de enviarlos por red
	void onlineFighterAttack(Transform* tr, Gun* g);
	//Recibe la nueva posición del enemigo en online
	void onMove_Enemy(Vector2D pos, Vector2D dir, float rot);

	Entity* getSoloFighter() { 
		return fighterSolo; 
	}

	Entity* getFriendFighter() {
		return friendCoop;
	}
private:
	// Para reaccionar al mensaje de que ha habido un choque entre el fighterSolo y un
	// un asteroide. Poner el caza en el centro con velocidad (0,0) y rotación 0. No
	// hace falta desactivar la entidad (no dibujarla si el juego está parado).
	void onCollision_FighterAsteroid();
	void onCollision_FighterBullet();

	//El juego esta en modo online
	void onOnline();
	// Para gestionar el mensaje de que ha acabado una ronda. Desactivar el sistema.
	void onRoundOver();
	// Para gestionar el mensaje de que ha empezado una ronda. Activar el sistema.
	void onRoundStart();
	// Indica si el sistema está activo o no (modificar el valor en onRoundOver y
	// onRoundStart, y en update no hacer nada si no está activo)
	bool active_;
	int state_ = 0; //0 - SOLO, 1 - COOP

	Game* game;
	SoundEffect* hitSound;

	Entity* fighterSolo;
	Transform* trSolo;
	FighterCtrl* fcSolo;
	DeAcceleration* daSolo;
	ShowAtOpposideSide* saosSolo;
	Gun* gSolo;

	Entity* friendCoop;
	Transform* trFriend;
	ShowAtOpposideSide* saosFriend;
	Gun* gFriend;
	FighterCtrl* fcFriend;
	DeAcceleration* daFriend;

	Entity* enemyCoop;
	Transform* trEnemy;
};


#endif /*FIGHTER_SYSTEM_H_*/