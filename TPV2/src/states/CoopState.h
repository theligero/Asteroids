#ifndef COOPSTATE_H_
#define COOPSTATE_H_

#include "GameState.h"
#include <SDL_net.h>
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../utils/Collisions.h"

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

class Game;

enum whichFighter { HOST, GUEST };

enum typeOfSocket { USERNAME, ENEMY, BULLET, PLAYER_DEAD };

using infoFinished = char[9];

class CoopState : public GameState
{
private:
	IPaddress ip;
	SDLNet_SocketSet socketSet;
	TCPsocket socket[NUM_SOCKETS];
	Entity** fighter = new Entity*[2];
	char** username = new char*[2];
	whichFighter chosenFighter;
public:
	CoopState(Game* g);
	virtual ~CoopState();

	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	void checkCollision();

	void sendBullet(Entity* bullet);

	void iAmAHost();
	void iAmAGuest();
};

#endif /*COOPSTATE_H_*/