#ifndef COOPSTATE_H_
#define COOPSTATE_H_

#include "GameState.h"
#include <SDL_net.h>
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../utils/Collisions.h"

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

class Game;

enum whichFighter { HOST, GUEST };

enum typeOfSocket { USERNAME, ENEMY, BULLET, PLAYER_DEAD };

class CoopState : public GameState
{
private:
	IPaddress ip;
	SDLNet_SocketSet socketSet;
	TCPsocket socket[NUM_SOCKETS];
	Entity** fighter = new Entity*[2];
	char** username = new char*[2];
	whichFighter chosenFighter;
	TCPsocket masterSocket;
public:
	CoopState(Game* g);
	virtual ~CoopState();

	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	bool checkCollision();

	void sendBullet(Entity* bullet);

	void iAmAHost();
	void iAmAGuest();
};

#endif /*COOPSTATE_H_*/