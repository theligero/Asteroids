#ifndef CLICKABLE_H_
#define CLICKABLE_H_

#include <SDL_mouse.h>
#include "Transform.h"
#include "../ecs/Component.h"
#include "../utils/Vector2D.h"

struct Clickable : public Component
{
private:
	Transform* tr;
	int mouseX = 0;
	int mouseY = 0;
public:
	constexpr static cmpId_type id = CLICKABLE;
	Clickable() : tr(nullptr) {}
	virtual ~Clickable() {}

	void initComponent() override;

	bool inTheRightX(const int& x) const;
	bool inTheRightY(const int& y) const;
};

#endif /*CLICKABLE_H_*/