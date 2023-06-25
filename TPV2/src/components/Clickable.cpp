#include <iostream>
#include <cassert>
#include "Clickable.h"
#include "../ecs/Entity.h"
#include "../sdlutils/SDLUtils.h"
#include "../ecs/Manager.h"

void Clickable::initComponent()
{
	tr = mngr->getComponent<Transform>(ent);
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