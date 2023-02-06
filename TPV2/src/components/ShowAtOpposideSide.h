#ifndef SHOW_AT_OPPOSIDE_SIDE_H_
#define SHOW_AT_OPPOSIDE_SIDE_H_

#include "../ecs/Component.h"
#include "Transform.h"

class ShowAtOpposideSide : public Component
{
public:
	ShowAtOpposideSide();
	virtual ~ShowAtOpposideSide() {}

	void update() override;
private:
	Transform* tr;
	int WindowWidth;
	int WindowHeight;
};

#endif /*SHOW_AT_OPPOSIDE_SIDE_H_*/