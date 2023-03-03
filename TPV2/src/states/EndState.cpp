#include "EndState.h"
#include "MainMenuState.h"

EndState::EndState(Game* g)
{
	game = g;
	backToMenu = new MenuButton({ 50,50 }, 150, 50, game->getArrayTex(RESUME), goToMenu, game);
}

EndState::~EndState()
{
	delete(backToMenu);
	delete(this);
}

void EndState::update()
{
	backToMenu->update();
}

void EndState::render()
{
	backToMenu->render();
}

void EndState::handleEvent()
{
	SDL_Event ev;

	while (SDL_PollEvent(&ev)) {
		switch (ev.type) {
		case SDL_MOUSEBUTTONDOWN:
			switch (ev.button.button) {
			case SDL_BUTTON_LEFT:
				backToMenu->handleEvent();
				break;
			}
			break;
		}
	}
}

bool EndState::onEnter()
{
	std::cout << "entrando en EndState\n";
	return true;
}

bool EndState::onExit()
{
	std::cout << "saliendo de EndState\n";
	return true;
}

void EndState::goToMenu(Game* game)
{
	game->getStateMachine()->changeState(new MainMenuState(game));
}
