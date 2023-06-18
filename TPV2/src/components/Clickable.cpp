#include <iostream>
#include <cassert>
#include "Clickable.h"
#include "../ecs/Entity.h"
#include "../sdlutils/SDLUtils.h"

void Clickable::initComponent()
{
	tr = ent->getComponent<Transform>(TRANSFORM);
	assert(tr != nullptr);
}

bool Clickable::inTheRightX(const int& x) const
{
	return x >= tr->getPos().getX() && x <= tr->getPos().getX() + tr->getW();
}

bool Clickable::inTheRightY(const int& y) const
{
	return y >= tr->getPos().getY() && y <= tr->getPos().getY() + tr->getH();
}

void Clickable::update()
{
	// SDL_GetGlobalMouseState(&mouseX, &mouseY);
	// int relativeX = 0, relativeY = 0;
	// if (sdlutils().window() == SDL_GetMouseFocus()) std::cout << "hola" << std::endl;
	//int x, y;
	//SDL_GetMouseState(&x, &y);
	//auto e = sdlutils().window();
	//e->x;
	//mouseX = x; mouseY = y;
	// mouseX += relativeX; mouseY += relativeY;
	//SDL_GetMouseState(&mouseX, &mouseY);
	//std::cout << mouseX << ", " << mouseY << std::endl;
	//if (inTheRightX() && inTheRightY()) {
	//	std::cout << "estoy dentro de un botón" << std::endl;
	//}

	//SDL_Event ev;


	//if (SDL_PollEvent(&ev)) {
	//	if (SDL_MOUSEMOTION == ev.type) SDL_GetMouseState(&mouseX, &mouseY);
	//	if (inTheRightX() && inTheRightY()) {
	//		if (SDL_MOUSEBUTTONDOWN == ev.type && SDL_BUTTON_LEFT == ev.button.button)
	//			std::cout << "he hecho click" << std::endl;
	//	}
	//}

	// std::cout << mouseX << ", " << mouseY << std::endl;

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
	//						// std::cout << "hola bitch \n";
	//						break;
	//					}
	//			}
	//			break;
	//		}
	//		break;
	//	}
	//}
}