#ifndef SHOW_AT_OPPOSIDE_SIDE_H_
#define SHOW_AT_OPPOSIDE_SIDE_H_

#include "../ecs/Component.h"
#include "Transform.h"

class ShowAtOpposideSide : public Component
{
public:
	constexpr static cmpId_type id = SHOW_AT_OPPOSIDE_SIDE;
	ShowAtOpposideSide(int w, int h) : WindowWidth(w), WindowHeight(h) {}
	virtual ~ShowAtOpposideSide() {}

	void initComponent() override;
	//void update() override;
private:
	Transform* tr;
	int WindowWidth;
	int WindowHeight;
};

#endif /*SHOW_AT_OPPOSIDE_SIDE_H_*/