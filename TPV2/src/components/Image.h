#ifndef IMAGE_H_
#define IMAGE_H_

#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"
#include "Transform.h"

class Image : public Component
{
public:
	constexpr static cmpId_type id = IMAGE;
	Image(Texture* t) : tex(t), tr(nullptr) {}
	virtual ~Image() {}
	//void render() override;
	void initComponent() override;

protected:
	Transform* tr;
	Texture* tex;
};

#endif /*IMAGE_H_*/