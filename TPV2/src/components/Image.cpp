#include "Image.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"

void Image::initComponent() 
{
	tr = mngr->getComponent<Transform>(ent);
	assert(tr != nullptr);
}

void Image::render()
{
	SDL_Rect dest = build_sdlrect(tr->getPos(),
		tr->getW(),
		tr->getH());
	tex->render(dest, tr->getRot());
}
