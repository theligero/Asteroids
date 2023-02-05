#include "Image.h"
#include "../ecs/Entity.h"

Image::Image(Texture* t)
{
	//tex = t;
	//tr = ent->getComponent<Transform>(TRANSFORM);
	//assert(tr != nullptr);
}

Image::~Image()
{
	// delete tex;
}

void Image::render()
{
	/*SDL_Rect dest = build_sdlrect(tr->getPos(),
		tr->getW(),
		tr->getH());
	tex->render(dest, tr->getRot());*/
}
