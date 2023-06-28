#include "OnlineSystem.h"
#include "BulletSystem.h"
#include "FighterSystem.h"
#include "../ecs/Manager.h"
#include "../components/Transform.h"
#include "../game/game.h"
#include <iostream>

void OnlineSystem::receive(const Message& m)
{
	switch (m.id) {
	case _m_IS_HOST:
		onHost();
		break;
	case _m_IS_GUEST:
		onGuest();
		break;
		break;
	case _m_MAIN_MENU:
		onRoundOver();
		break;
	case _m_BULLET_SHOT:
		onSendBullet(m.shot_bullet_data.pos, m.shot_bullet_data.vel, m.shot_bullet_data.rot);
		break;
	case _m_FIGHTER_BULLET_HIT:
		onSendDeath();
		break;
	default:
		break;
	}
}

void OnlineSystem::initSystem()
{
	SDLNet_Init();

	hitSound = game->getArraySound(FIGHTER_EXPLOSION);
	shootSound = game->getArraySound(SHOOT);
}

void OnlineSystem::update()
{

	char buffer[256];

	infoTransform tr;
	infoFinished fin;

	if (active_) {
		auto fighterTr = man->getComponent<Transform>(man->getSystem<FighterSystem>()->getFriendFighter());
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
						if (result == sizeof(infoTransform)) {
							std::memcpy(&tr, buffer, sizeof(infoTransform));
							if (typeOfSocket(i) == BULLET) {
								//MENSAJE ME DISPARAN
								shootSound->play();
								Message m;
								m.id = _m_BULLET_SHOT;
								m.shot_bullet_data.pos = tr.pos;
								m.shot_bullet_data.vel = tr.dir;
								m.shot_bullet_data.width = 5;
								m.shot_bullet_data.height = 20;
								m.shot_bullet_data.rot = tr.rot;
								man->getSystem<BulletSystem>()->receive(m);
							}
							else if (typeOfSocket(i) == ENEMY) {
								Message m;
								m.id = _m_MOVE_ENEMY;
								m.move_enemy_data.enemyPos = tr.pos;
								m.move_enemy_data.enemyDir = tr.dir;
								m.move_enemy_data.enemyRot = tr.rot;
								man->send(m);
							}
						}
						else if (result == sizeof(infoFinished)) {
							std::memcpy(&fin, buffer, sizeof(infoFinished));
							if (typeOfSocket(i) == PLAYER_DEAD && strcmp(fin, "TERMINADO") == 0) {
								//MENSAJE FIN PARTIDA
								hitSound->play();
								Message m;
								m.id = _m_ENEMY_DEAD;
								man->send(m);
								active_ = false;
								//Prueba o no si el active = false es necesario
								std::cout << "pinga" << std::endl;
								return;
							}
						}
					}
				}
			}
		}

		if (fighterTr != nullptr && active_) {
			tr.dir = fighterTr->getDir();
			tr.pos = fighterTr->getPos();
			tr.rot = fighterTr->getRot();
			SDLNet_TCP_Send(socket[ENEMY], &tr, sizeof(infoTransform));
		}
	}

}

void OnlineSystem::onRoundOver()
{
	if(active_){
		active_ = false;
		if (host) {
			SDLNet_TCP_Close(masterSocket);
			SDLNet_TCP_DelSocket(socketSet, masterSocket);
			masterSocket = nullptr;
		}

		for (int i = 0; i < NUM_SOCKETS; i++) {
			SDLNet_TCP_Close(socket[i]);
			SDLNet_TCP_DelSocket(socketSet, socket[i]);
			socket[i] = nullptr;
		}
	}
}


void OnlineSystem::onHost()
{
	active_ = true;
	host = true;
	char buffer[256];
	int result = 0;

	if (SDLNet_ResolveHost(&ip, nullptr, 1234) < 0) { std::cout << "error\n"; }
	masterSocket = SDLNet_TCP_Open(&ip);
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

void OnlineSystem::onGuest()
{
	active_ = true;
	host = false;
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

void OnlineSystem::onSendBullet(Vector2D pos, Vector2D vel, float rot)
{
	infoTransform aux(pos, vel, rot);
	SDLNet_TCP_Send(socket[BULLET], &aux, sizeof(infoTransform));
}

void OnlineSystem::onSendDeath()
{
	infoFinished aux = "TERMINADO";
	SDLNet_TCP_Send(socket[PLAYER_DEAD], &aux, sizeof(infoFinished));
}
