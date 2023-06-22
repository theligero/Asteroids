#include "CoopState.h"
#include "../game/game.h"

CoopState::CoopState(Game* g)
{
	game = g;
	auto& man = *Manager::instance();

	SDLNet_Init();

	for (int i = 0; i < 2; ++i) {
		username[i] = new char[MAX_CHARACTERS];
	}

	// std::cin.ignore();
	std::cout << "Introduzca su nombre de usuario: ";
	std::cin.getline(username[chosenFighter], MAX_CHARACTERS + 1);
	std::cout << "Tu nombre de usuario es: " << username[chosenFighter] << std::endl;

	char a;
	std::cout << "Quieres ser el host o el invitado? [H/I]: ";
	std::cin >> a;
	std::cout << std::endl;

	if (a == 'H' || a == 'h') {
		chosenFighter = HOST;
		iAmAHost();
	}
	else {
		chosenFighter = GUEST;
		iAmAGuest();
	}

	for (int i = 0; i < 2; ++i) {
		fighter[i] = man.addEntity(_grp_FIGHTER);
		fighter[i]->addComponent<Transform>(TRANSFORM, Vector2D(i * (WINDOW_WIDTH - 35), 300), Vector2D(0, 0), 35, 30, (180 * i) + 90);
		// fighter[i]->addComponent<Health>(HEALTH, WINDOW_WIDTH, WINDOW_HEIGHT, game->getArrayTexture(HEART));
		fighter[i]->addComponent<Image>(IMAGE, game->getArrayTexture(FIGHTER));
		fighter[i]->addComponent<ShowAtOpposideSide>(SHOW_AT_OPPOSIDE_SIDE, WINDOW_WIDTH, WINDOW_HEIGHT);
		if (i == chosenFighter) {
			fighter[i]->addComponent<Gun>(GUN, game->getArraySound(SHOOT), game->getArrayTexture(FIRE), this, WINDOW_WIDTH, WINDOW_HEIGHT);
			fighter[i]->addComponent<FighterCtrl>(FIGHTER_CTRL, game->getArraySound(THRUST), game);
			fighter[i]->addComponent<DeAcceleration>(DEACCELERATION);
		}
		fighter[i]->getComponent<Transform>(TRANSFORM)->getPos();

		// texto que sigue a fighter[i] con el componente Follow
	}
}

CoopState::~CoopState()
{
}

void CoopState::update()
{
	auto& man = *Manager::instance();

	InputHandler::instance()->refresh();
	checkCollision();

	char buffer[256];

	Vector2D aux;
	infoTransform tr;
	float f;
	whichFighter enemyFighter = static_cast<whichFighter>(chosenFighter ^ 1);

	auto fighterTr = fighter[chosenFighter]->getComponent<Transform>(TRANSFORM);
	auto enemyFighterTr = fighter[enemyFighter]->getComponent<Transform>(TRANSFORM);

	man.update();

	if (SDLNet_CheckSockets(socketSet, SDL_MAX_UINT32) > 0) {
		int result = 0;
		// TODO II: PROCESS DATA on client sockets
		for (int i = 0; i < NUM_SOCKETS; i++) {
			if (socket[i] != nullptr && SDLNet_SocketReady(socket[i])) {
				result = SDLNet_TCP_Recv(socket[i], buffer, 255);
				if (result <= 0) {
					SDLNet_TCP_Close(socket[i]);
					SDLNet_TCP_DelSocket(socketSet, socket[i]);
					socket[i] = nullptr;
				}
				else {
					if (result == sizeof(Vector2D)) {
						std::memcpy(&aux, buffer, sizeof(Vector2D));
						if (typeOfSocket(i) == POSITION) enemyFighterTr->setPos(aux);
						else if (typeOfSocket(i) == DIRECTION) enemyFighterTr->setDir(aux);
					}
					else if (result == sizeof(infoTransform)) {
						std::memcpy(&tr, buffer, sizeof(infoTransform));
						if (typeOfSocket(i) == BULLET) {
							auto bullet = man.addEntity(_grp_BULLETS);
							bullet->addComponent<Transform>(TRANSFORM, tr.pos, tr.dir, 5, 20, tr.rot);
							bullet->addComponent<Image>(IMAGE, game->getArrayTexture(FIRE));
							bullet->addComponent<DisableOnExit>(DISABLE_ON_EXIT, WINDOW_WIDTH, WINDOW_HEIGHT);
							game->getArraySound(SHOOT)->play();
						}
					}
					else if (result == sizeof(float)) {
						std::memcpy(&f, buffer, sizeof(float));
						if (typeOfSocket(i) == ROTATION) enemyFighterTr->setRot(f);
					}
				}
			}
		}
	}
	if (fighter[chosenFighter]->isAlive()) {
		SDLNet_TCP_Send(socket[POSITION], &fighterTr->getPos(), sizeof(Vector2D));
		SDLNet_TCP_Send(socket[DIRECTION], &fighterTr->getDir(), sizeof(Vector2D));
		SDLNet_TCP_Send(socket[ROTATION], &fighterTr->getRot(), sizeof(float));
	}
	else {
		SDLNet_TCP_Send(socket[PLAYER_DEAD], &fighter[chosenFighter]->isAlive(), sizeof(bool));
	}


	man.refresh();
}

void CoopState::render()
{
	Manager::instance()->render();
}

bool CoopState::onEnter()
{
	std::cout << "Entrando en CoopState\n";
	return true;
}

bool CoopState::onExit()
{
	std::cout << "Saliendo de CoopState\n";
	return true;
}

void CoopState::checkCollision()
{
	auto& man = *Manager::instance();

	for (auto& e : man.getEntities(_grp_BULLETS)) {
		auto trBullet = e->getComponent<Transform>(TRANSFORM);
		for (auto& i : man.getEntities(_grp_FIGHTER)) {
			auto trFighter = i->getComponent<Transform>(TRANSFORM);
			if (Collisions::collidesWithRotation(trBullet->getPos(), trBullet->getW(), trBullet->getH(), trBullet->getRot(),
				trFighter->getPos(), trFighter->getW(), trFighter->getH(), trFighter->getRot())) {
				game->getArraySound(FIGHTER_EXPLOSION)->play(0, 1);
				i->setAlive(false);
				std::cout << "me han dado :(" << std::endl;
			}
		}
	}
}

void CoopState::sendBullet(Entity* bullet)
{
	auto tr = bullet->getComponent<Transform>(TRANSFORM);
	infoTransform aux(tr->getPos(), tr->getDir(), tr->getRot());
	SDLNet_TCP_Send(socket[BULLET], &aux, sizeof(infoTransform));
}

void CoopState::iAmAHost()
{
	char buffer[256];
	int result = 0;

	if (SDLNet_ResolveHost(&ip, nullptr, 1234) < 0) { std::cout << "error\n"; }
	TCPsocket masterSocket = SDLNet_TCP_Open(&ip);
	if (!masterSocket) { std::cout << "error\n"; }
	socketSet = SDLNet_AllocSocketSet(NUM_SOCKETS + 1);
	SDLNet_TCP_AddSocket(socketSet, masterSocket);
	for (int i = 0; i < NUM_SOCKETS; i++) { socket[i] = nullptr; }
	std::cout << "Esperando al otro jugador...\n";
	while (socket[NUM_SOCKETS - 1] == nullptr) {
		if (SDLNet_CheckSockets(socketSet, SDL_MAX_UINT32) > 0) {
			// TODO I: PROCESS DATA on masterSocket
			if (SDLNet_SocketReady(masterSocket)) {
				TCPsocket client = SDLNet_TCP_Accept(masterSocket);
				// look for a free slot in the array
				int j = 0;
				while (j < NUM_SOCKETS && socket[j] != nullptr) j++;
				if (j < NUM_SOCKETS) {
					socket[j] = client;
					SDLNet_TCP_AddSocket(socketSet, client);
					buffer[0] = 0;
					SDLNet_TCP_Send(client, buffer, 1);
				}
				else {
					buffer[0] = 1;
					SDLNet_TCP_Send(client, buffer, 1);
					SDLNet_TCP_Close(client);
				}
			}

			// TODO II: PROCESS DATA on client sockets
			for (int i = 0; i < NUM_SOCKETS; i++) {
				if (socket[i] != nullptr && SDLNet_SocketReady(socket[i])) {
					result = SDLNet_TCP_Recv(socket[i], buffer, 255);

					if (result <= 0) {
						 SDLNet_TCP_Close(socket[i]);
						 SDLNet_TCP_DelSocket(socketSet, socket[i]);
						 socket[i] = nullptr;
					}
					else {
						 std::cout << "Client " << i << " says: " << buffer << std::endl;
						 SDLNet_TCP_Send(socket[i], "Received!", 10);
					}
				}
			}

		}
	}
}

void CoopState::iAmAGuest()
{
	std::string host;
	char buffer[256];
	int result = 0;
	bool done = true;

	socketSet = SDLNet_AllocSocketSet(NUM_SOCKETS);

	std::cin.ignore();
	std::cout << "Introduzca la IP del host: ";
	std::cin >> host;
	std::cout << std::endl;

	if (SDLNet_ResolveHost(&ip, host.c_str(), 1234) < 0) { std::cout << "error\n"; }
	TCPsocket conn = SDLNet_TCP_Open(&ip);
	if (!conn) { std::cout << "error\n"; }

	// TODO I: WAIT FOR CONFIRMATION MESSAGE
	result = SDLNet_TCP_Recv(conn, buffer, 1);
	if (result < 0) {
		std::cout << "error\n"; // something went wrong
	}
	else if (result == 0) {
		std::cout << "The server closed the connection …" << std::endl;
	}
	else {
		if (buffer[0] == 0) {
			std::cout << "Connected!" << std::endl;
			socket[USERNAME] = conn;
			done = false;
		}
		else {
			std::cout << "Connection refused!" << std::endl;
			done = true;
		}
	}

	for (int i = 1; i < NUM_SOCKETS; ++i) {
		socket[i] = SDLNet_TCP_Open(&ip);
		SDLNet_TCP_AddSocket(socketSet, socket[i]);
	}
}
