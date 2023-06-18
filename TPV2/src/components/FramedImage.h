#ifndef FRAMED_IMAGE_H_
#define FRAMED_IMAGE_H_

#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/VirtualTimer.h"
#include "Image.h"

const int TIME_PER_FRAME = 50;

class FramedImage : public Component
{
public:
	constexpr static cmpId_type id = ecs::FRAMED_IMAGE;
	FramedImage(Texture* t, int rows, int cols) : 
		tex(t), tr(nullptr) { textFrame.w = t->width() / cols; textFrame.h = t->height() / rows; clock = new VirtualTimer();}
	virtual ~FramedImage() {}
	void initComponent() override;
	void render() override;
	void update() override;
private:
	SDL_Rect textFrame;
	VirtualTimer* clock;
	Transform* tr;
	Texture* tex;
};

#endif /*FRAMED_IMAGE_H_*/