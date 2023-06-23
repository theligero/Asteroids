#ifndef FRAMED_IMAGE_H_
#define FRAMED_IMAGE_H_

#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/VirtualTimer.h"
#include "Transform.h"
#include "../game/ecs_def.h"

const int TIME_PER_FRAME = 50;


struct FramedImage : public Component
{
public:
	constexpr static cmpId_type id = ecs::FRAMED_IMAGE;
	FramedImage(Texture* t, int rows, int cols) : 
		tex(t), tr(nullptr) { textFrame.w = t->width() / cols; textFrame.h = t->height() / rows; clock = new VirtualTimer();}
	virtual ~FramedImage() {}
	inline Texture* getTexture() { return tex; }
	inline SDL_Rect& getTextFrame() { return textFrame; }
	void initComponent() override;
private:
	SDL_Rect textFrame;
	VirtualTimer* clock;
	Transform* tr;
	Texture* tex;
};

#endif /*FRAMED_IMAGE_H_*/