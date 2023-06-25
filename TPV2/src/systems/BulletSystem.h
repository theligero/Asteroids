#ifndef BULLET_SYSTEM_H_
#define BULLET_SYSTEM_H_

#include "../ecs/System.h"
#include "../utils/Vector2D.h"

const int wWidth = 800;
const int wHeight = 600;

class Entity;

class BulletSystem : public System {
public:
	BulletSystem() : active_(true) {}
	constexpr static ecs::sysId_type id = ecs::_sys_BULLET;
	// Reaccionar a los mensajes recibidos (llamando a métodos correspondientes).
	void receive(const Message& m) override;
	// Inicializar el sistema, etc.
	void initSystem() override;
	// Si el juego está parado no hacer nada, en otro caso mover las balas y
	// desactivar las que salen de la ventana como en la práctica 1.
	void update() override;
private:
	// Para gestionar el mensaje de que el jugador ha disparado. Añadir una bala al
	// juego, como en la práctica 1. Recuerda que la rotación de la bala sería
	// vel.angle(Vector2D(0.0f,-1.0f))
	void shoot(Vector2D pos, Vector2D vel, double width, double height, float rot);
	//El juego esta en modo online
	void onOnline();
	//EL juego termina modo online
	void onOnlineOver();
	// Para gestionar el mensaje de que ha habido un choque entre una bala y un
	// asteroide. Desactivar la bala “b”.
	void onCollision_BulletAsteroid(Entity* b);
	// Para gestionar el mensaje de que ha habido un choque entre una bala y una
	// nave. Desactivar la bala “b”.
	void onCollision_Bullet_Fighter(Entity* b);
	// Para gestionar el mensaje de que ha acabado la ronda. Desactivar todas las
	// balas, y desactivar el sistema.
	void onRoundOver(bool pause);
	// Para gestionar el mensaje de que ha empezado una ronda. Activar el sistema.
	void onRoundStart(bool pause);
	// Indica si el sistema está activo o no (modificar el valor en onRoundOver y
	// onRoundStart, y en update no hacer nada si no está activo)
	bool active_;
};

#endif /*BULLET_SYSTEM_H_*/