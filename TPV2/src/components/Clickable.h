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
	int mouseX = 0;
	int mouseY = 0;
public:
	Clickable() : tr(nullptr) {}
	virtual ~Clickable() {}

	void initComponent() override;
	void update() override;

	bool inTheRightX(const int& x) const;
	bool inTheRightY(const int& y) const;
};

#endif /*CLICKABLE_H_*/