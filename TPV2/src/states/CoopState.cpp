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
		fighter[i]->addComponent<DeAcceleration>(DEACCELERATION);
		// fighter[i]->addComponent<Health>(HEALTH, WINDOW_WIDTH, WINDOW_HEIGHT, game->getArrayTexture(HEART));
		fighter[i]->addComponent<Image>(IMAGE, game->getArrayTexture(FIGHTER));
		fighter[i]->addComponent<ShowAtOpposideSide>(SHOW_AT_OPPOSIDE_SIDE, WINDOW_WIDTH, WINDOW_HEIGHT);
		if (i == chosenFighter) {
			fighter[i]->addComponent<Gun>(GUN, game->getArraySound(SHOOT), game->getArrayTexture(FIRE), WINDOW_WIDTH, WINDOW_HEIGHT);
			fighter[i]->addComponent<FighterCtrl>(FIGHTER_CTRL, game->getArraySound(THRUST), game);
		}
		fighter[i]->getComponent<Transform>(TRANSFORM)->getPos();
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

	man.update();
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
				i->setAlive(false);
				std::cout << "me han dado :(" << std::endl;
			}
		}
	}
}

void CoopState::iAmAHost()
{
	SDLNet_ResolveHost(&ip, nullptr, 1234);

	server = SDLNet_TCP_Open(&ip);

	//auto fighterTr = fighter[chosenFighter]->getComponent<Transform>(TRANSFORM);

	std::cout << "Esperando al otro jugador...\n";

	while (true) {
		client = SDLNet_TCP_Accept(server);
		if (client) {
			std::cout << "conectado!" << std::endl;
			// SDLNet_TCP_Send(client, &fighterTr, 255);
		}
	}

	//SDLNet_TCP_Close(server);
}

void CoopState::iAmAGuest()
{
	std::string host;

	std::cin.ignore();
	std::cout << "Introduzca la IP del host: ";
	std::cin >> host;
	std::cout << std::endl;

	SDLNet_ResolveHost(&ip, host.c_str(), 1234);
}
