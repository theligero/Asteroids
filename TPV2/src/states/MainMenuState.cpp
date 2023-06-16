#include "MainMenuState.h"

MainMenuState::MainMenuState(Game* g)
{
	game = g;

	sdlutils().showCursor(); 
	// SDL_SetRelativeMouseMode(SDL_TRUE);

	auto& man = *Manager::instance();

	jugarSolo = man.addEntity();
	jugarSolo->addComponent<Transform>(TRANSFORM, Vector2D(WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 2 - 75), Vector2D(), 200, 100, 0);
	jugarSolo->addComponent<Image>(IMAGE, game->getArrayTexture(SOLO));
	jugarSolo->addComponent<Clickable>(CLICKABLE);
	
	jugarCoop = man.addEntity();
	jugarCoop->addComponent<Transform>(TRANSFORM, Vector2D(WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 2 + 75), Vector2D(), 200, 100, 0);
	jugarCoop->addComponent<Image>(IMAGE, game->getArrayTexture(COOP));
	jugarCoop->addComponent<Clickable>(CLICKABLE);
	
	// MenuButton* jugarSolo = new MenuButton({ 50,50 }, 150, 50, game->getArrayTexture(PLAY), beginGame, game);
	// MenuButton* jugarCoop = new MenuButton({ 50,200 }, 150, 50, game->getArrayTexture(COOP), loadGame, game);
	//MenuButton* salir = new MenuButton({ 50,400 }, 150, 50, game->getArrayTex(EXIT), endGame, game);

	// menuButtons.push_back(jugarSolo);
	// menuButtons.push_back(jugarCoop);
	//sceneObjects.push_back(salir);
}

MainMenuState::~MainMenuState()
{

}

void MainMenuState::update()
{
	Manager::instance()->update();
}

void MainMenuState::render()
{
	Manager::instance()->render();
	//for (auto it : sceneObjects) {
	//	it->render();
	//}
}

void MainMenuState::handleEvent()
{	
	// Manager::instance()->handleEvent();
	
	//SDL_Event ev;

	//while (SDL_PollEvent(&ev)) {
	//	switch (ev.type) {
	//	case SDL_MOUSEBUTTONDOWN:
	//		switch (ev.button.button) {
	//		case SDL_BUTTON_LEFT:
	//			//std::cout << "click " << name << "\n";
	//			//checkBounds();
	//			for (auto it : sceneObjects) {
	//					auto objeto = dynamic_cast<MenuButton*>(it);
	//					objeto->handleEvent();
	//					if (objeto->getPressed()) {
	//						std::cout << "hola bitch \n";
	//						break;
	//					}
	//			}
	//			break;
	//		}
	//		break;
	//	}
	//}
}

bool MainMenuState::onEnter()
{
	std::cout << "entrando en MenuState\n";
	return true;
}

bool MainMenuState::onExit()
{
	std::cout << "saliendo de MenuState\n";
	return true;
}

void MainMenuState::beginGame(Game* game)
{
	game->getStateMachine()->changeState(new PlayState(game));
	//std::cout << "hola";
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
