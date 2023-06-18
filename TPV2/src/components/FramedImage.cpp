#include "FramedImage.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"

void FramedImage::initComponent()
{
	tr = mngr->getComponent<Transform>(ent);
	assert(tr != nullptr);
}

void FramedImage::render()
{
	SDL_Rect dest = build_sdlrect(tr->getPos(),
		tr->getW(),
		tr->getH());
	tex->render(textFrame, dest, tr->getRot());
	clock->reset();
}

void FramedImage::update()
{
	textFrame.x = textFrame.w * int(((SDL_GetTicks() / TIME_PER_FRAME) % 6));
	textFrame.y = textFrame.h * int(((SDL_GetTicks() / (TIME_PER_FRAME * 6)) % 5));
}
