#ifndef ASTEROIDS_SYSTEM_H_
#define ASTEROIDS_SYSTEM_H_

#include "../sdlutils/SDLUtils.h"
#include "../ecs/System.h"

const int MAX_ASTEROIDS = 30;
const int INI_ASTEROIDS = 10;

class Entity;
class SoundEffect;
class Game;

class AsteroidsSystem : public System {
public:
	AsteroidsSystem(Game *g) : numOfAsteroids_(0), active_(true), game(g), lastTime (0), goldAsteroid(nullptr), normalAsteroid(nullptr), fighter(nullptr), asteroidDestroyed(nullptr) {}
	constexpr static ecs::sysId_type id = ecs::_sys_ASTEROIDS;
	// Reaccionar a los mensajes recibidos (llamando a métodos correspondientes).
	void receive(const Message& m) override;
	// Inicializar el sistema, etc.
	void initSystem() override;
	// Si el juego está parado no hacer nada, en otro caso mover los asteroides como
	// en la práctica 1 y generar 1 asteroide nuevo cada 5 segundos (aparte
	// de los 10 al principio de cada ronda).
	void update() override;

	//Crea n asteroides cuando se llama.
	void createAsteroids(int n);

	//Se encarga de crear asteroides cada cierto tiempo
	void addAsteroidFrequently();
private:
	// Para gestionar el mensaje de que ha habido un choque de un asteroide con una
	// bala. Desactivar el asteroide “a” y crear 2 asteroides como en la práctica 1,
	// y si no hay más asteroides enviar un mensaje correspondiente.
	void onCollision_AsteroidBullet(Entity* a);
	// Para gestionar el mensaje de que ha acabado la ronda. Desactivar todos los
	// asteroides, y desactivar el sistema.
	void onRoundOver(bool pause);
	// Para gestionar el mensaje de que ha empezado una ronda. Activar el sistema y
	// añadir los asteroides iniciales (como en la práctica 1).
	void onRoundStart(bool pause);
	// El número actual de asteroides en el juego (recuerda que no puede superar un
	// límite)
	Uint8 numOfAsteroids_;
	// Indica si el sistema está activo o no (modificar el valor en onRoundOver y
	// onRoundStart, y en update no hacer nada si no está activo)
	bool active_;
	//Último momento un asteroide fue creado
	int lastTime;
	//Puntero al juego
	Game* game;
	//Texturas de los asteroides
	Texture* goldAsteroid;
	Texture* normalAsteroid;
	//Entidad del fighterSolo
	Entity* fighter;
	//Sonido de choque
	SoundEffect* asteroidDestroyed;
};

#endif /*ASTEROIDS_SYSTEM_H_*/