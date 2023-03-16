#include "Health.h"
#include "../ecs/Entity.h"
#include <iostream>

void Health::decreaseLives()
{
	if (livesCount > 0) {
		--livesCount;
	}
}

//void Health::render()
//{
//	SDL_Rect dest;
//	Vector2D pos = { 10, 10 };
//	Vector2D posChange = { 30, 0 };
//	for (int i = 0; i < livesCount; i++) {
//		dest = build_sdlrect(pos,
//			tr->getW(),
//			tr->getH());
//		tex->render(dest, 0);
//		pos = pos + posChange;
//	}
//}

void Health::initComponent()
{
	tr = ent->getComponent<Transform>(TRANSFORM);
	assert(tr != nullptr);
}