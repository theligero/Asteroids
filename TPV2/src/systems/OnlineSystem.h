#ifndef ONLINE_SYSTEM_H_
#define ONLINE_SYSTEM_H_

#include "../ecs/System.h"
#include "../ecs/Entity.h"
#include <SDL_net.h>
//#include "../game/game.h"

class Game;
class SoundEffect;

using infoFinished = char[10];

const int MAX_CHARACTERS = 10;
const int NUM_SOCKETS = 4;

struct infoTransform {
	infoTransform(Vector2D p, Vector2D d, float r) :
		pos(p), dir(d), rot(r) {}
	infoTransform() : pos(), dir(), rot() {}
	Vector2D pos;
	Vector2D dir;
	float rot;
};

enum whichFighter { HOST, GUEST };

enum typeOfSocket { USERNAME, ENEMY, BULLET, PLAYER_DEAD };

class Game;
class Transform;

class OnlineSystem : public System {
public:
	OnlineSystem(Game* g) : game(g) {}
	constexpr static ecs::sysId_type id = ecs::_sys_ONLINE;
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
	Entity* getFighter() {
		return fighter;
	}
private:
	
	// Para gestionar el mensaje de que ha acabado una ronda. Desactivar el sistema.
	void onRoundOver();
	//Gestiona el mensaje de si el jugador es host o invitado;
	void onHost();
	void onGuest();
	//Envía la bala disparada por el jugador
	void onSendBullet(Vector2D pos, Vector2D vel, float rot);
	//Envío que he muerto al otro jugador
	void onSendDeath();
	// Indica si el sistema está activo o no (modificar el valor en onRoundOver y
	// onRoundStart, y en update no hacer nada si no está activo)
	bool active_;

	Game* game;
	Entity* fighter;
	Transform* tr;

	SoundEffect* shootSound;
	SoundEffect* hitSound;

	IPaddress ip;
	SDLNet_SocketSet socketSet;
	TCPsocket socket[NUM_SOCKETS];
	char** username = new char* [2];
	whichFighter chosenFighter;
	TCPsocket masterSocket;

	bool host;
};


#endif /*FIGHTER_SYSTEM_H_*/