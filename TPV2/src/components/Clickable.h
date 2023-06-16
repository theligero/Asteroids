#ifndef CLICKABLE_H_
#define CLICKABLE_H_

#include <SDL_mouse.h>
#include "Transform.h"
#include "../ecs/Component.h"
#include "../utils/Vector2D.h"

class Clickable : public Component
{
private:
	Transform* tr;
	int mouseX;
	int mouseY;
public:
	Clickable() : Component(), tr(nullptr) {
		SDL_GetMouseState(&mouseX, &mouseY);
	}
	virtual ~Clickable() {}

	void initComponent() override;
	void update() override;

	bool inTheRightX() const;
	bool inTheRightY() const;
};

#endif /*CLICKABLE_H_*/