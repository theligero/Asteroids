#include "MainMenuState.h"

MainMenuState::MainMenuState(Game* g)
{
	game = g;

	MenuButton* jugar = new MenuButton({ 50,50 }, 150, 50, game->getArrayTex(PLAY), beginGame, game);
	MenuButton* cargar = new MenuButton({ 50,200 }, 150, 50, game->getArrayTex(LOAD), loadGame, game);
	MenuButton* salir = new MenuButton({ 50,400 }, 150, 50, game->getArrayTex(EXIT), endGame, game);

	sceneObjects.push_back(jugar);
	sceneObjects.push_back(cargar);
	sceneObjects.push_back(salir);
}

MainMenuState::~MainMenuState()
{
	for (auto e : sceneObjects) {
		delete(e);
	}
}

void MainMenuState::update()
{
	for (auto it : sceneObjects) {
		it->update();
	}
}

void MainMenuState::render()
{
	for (auto it : sceneObjects) {
		it->render();
	}
}

void MainMenuState::handleEvent()
{	

	SDL_Event ev;

	while (SDL_PollEvent(&ev)) {
		switch (ev.type) {
		case SDL_MOUSEBUTTONDOWN:
			switch (ev.button.button) {
			case SDL_BUTTON_LEFT:
				//std::cout << "click " << name << "\n";
				//checkBounds();
				for (auto it : sceneObjects) {
						auto objeto = dynamic_cast<MenuButton*>(it);
						objeto->handleEvent();
						if (objeto->getPressed()) {
							std::cout << "hola bitch \n";
							break;
						}
				}
				break;
			}
			break;
		}
	}
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
	game->setExit();
	//std::cout << "hola";
}

void MainMenuState::loadGame(Game* game)
{

	string nombre;
		cout << "\n";
		cin >> nombre;
		string aux = "../saveGames/save" + nombre + ".dat";
		fstream loadInput;
	
		loadInput.open(aux);
	
		if (!loadInput) throw FileNotFoundError(nombre + ".dat");

		game->getStateMachine()->changeState(new PlayState(game, loadInput));

}
