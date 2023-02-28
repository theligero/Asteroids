#ifndef FRAMED_IMAGE_H_
#define FRAMED_IMAGE_H_

#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"
#include "Image.h"

class FramedImage : public Image
{
public:
	FramedImage(Texture* t, int rows, int cols) : 
		Image(t) { currentFrame.w = t->width() / cols; currentFrame.h = t->height() / rows; }
	virtual ~FramedImage() {}
	void render() override;
	void update() override;
private:
	SDL_Rect currentFrame;
};

#endif /*FRAMED_IMAGE_H_*/