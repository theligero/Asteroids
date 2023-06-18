#include "MainMenuState.h"

MainMenuState::MainMenuState(Game* g)
{
	game = g;

	sdlutils().showCursor(); 

	auto& man = *Manager::instance();

	title = man.addEntity();
	title->addComponent<Transform>(TRANSFORM, Vector2D(WINDOW_WIDTH / 2 - 300, WINDOW_HEIGHT / 8), Vector2D(), 600, 100, 0);
	title->addComponent<Image>(IMAGE, game->getArrayTexture(TITLE));

	jugarSolo = man.addEntity(_grp_BUTTON);
	auto trSolo = jugarSolo->addComponent<Transform>(TRANSFORM, Vector2D(WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 2 - 75), Vector2D(), 200, 100, 0);
	jugarSolo->addComponent<Image>(IMAGE, game->getArrayTexture(SOLO));
	jugarSolo->addComponent<Clickable>(CLICKABLE);
	
	jugarCoop = man.addEntity(_grp_BUTTON);
	auto trCoop = jugarCoop->addComponent<Transform>(TRANSFORM, Vector2D(WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 2 + 75), Vector2D(), 200, 100, 0);
	jugarCoop->addComponent<Image>(IMAGE, game->getArrayTexture(COOP));
	jugarCoop->addComponent<Clickable>(CLICKABLE);
}

void MainMenuState::update()
{
	auto& man = *Manager::instance();

	man.update();

	SDL_Event ev;

	if (SDL_PollEvent(&ev)) {
		if (SDL_MOUSEMOTION == ev.type) SDL_GetMouseState(&mouseX, &mouseY);
		if (SDL_MOUSEBUTTONDOWN == ev.type) {
			if (SDL_BUTTON_LEFT == ev.button.button) {
				for (auto& e : man.getEntities(_grp_BUTTON)) {
					auto i = e->getComponent<Clickable>(CLICKABLE);
					if (i->inTheRightX(mouseX) && i->inTheRightY(mouseY)) {
						if (e == jugarSolo) beginSoloGame(game);
						else if (e == jugarCoop) beginCoopGame(game);
					}
				}
			}
		}
	}
}

void MainMenuState::render()
{
	Manager::instance()->render();
}

void MainMenuState::handleEvent()
{

}

bool MainMenuState::onEnter()
{
	std::cout << "entrando en MenuState\n";
	return true;
}

bool MainMenuState::onExit()
{
	auto& man = *Manager::instance();

	for (auto& e : man.getEntities(_grp_BUTTON)) {
		e->setAlive(false);
	}

	title->setAlive(false);

	sdlutils().hideCursor();

	std::cout << "saliendo de MenuState\n";
	return true;
}

void MainMenuState::beginSoloGame(Game* game)
{
	game->getStateMachine()->changeState(new PlayState(game));
	//std::cout << "hola";
}

void MainMenuState::beginCoopGame(Game* game)
{
	game->getStateMachine()->changeState(new CoopState(game));
}

void MainMenuState::endGame(Game* game)
{
	game->getStateMachine()->popState();
	// game->setExit();
	//std::cout << "hola";
}

void MainMenuState::loadGame(Game* game)
{

	//std::string nombre;
	//	std::cout << "\n";
	//	std::cin >> nombre;
	//	std::string aux = "../saveGames/save" + nombre + ".dat";
	//	fstream loadInput;
	//
	//	loadInput.open(aux);
	//
	//	if (!loadInput) throw FileNotFoundError(nombre + ".dat");

	//	game->getStateMachine()->changeState(new PlayState(game, loadInput));

}
