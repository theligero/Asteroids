#include "FramedImage.h"

void FramedImage::render()
{
	SDL_Rect dest = build_sdlrect(tr->getPos(),
		tr->getW(),
		tr->getH());
	tex->render(currentFrame, dest, tr->getRot());
}

void FramedImage::update()
{

}
