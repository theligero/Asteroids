#include "Image.h"
#include "../ecs/Entity.h"

void Image::initComponent() 
{
	tr = ent->getComponent<Transform>();
	assert(tr != nullptr);
}

void Image::render()
{
	SDL_Rect dest = build_sdlrect(tr->getPos(),
		tr->getW(),
		tr->getH());
	tex->render(dest, tr->getRot());
}
