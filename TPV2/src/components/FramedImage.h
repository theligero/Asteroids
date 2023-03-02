#ifndef FRAMED_IMAGE_H_
#define FRAMED_IMAGE_H_

#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/VirtualTimer.h"
#include "Image.h"

const int TIME_PER_FRAME = 50;

class FramedImage : public Image
{
public:
	FramedImage(Texture* t, int rows, int cols) : 
		Image(t) { textFrame.w = t->width() / cols; textFrame.h = t->height() / rows; clock = new VirtualTimer();}
	virtual ~FramedImage() {}
	void render() override;
	void update() override;
private:
	SDL_Rect textFrame;
	VirtualTimer* clock;

};

#endif /*FRAMED_IMAGE_H_*/