#ifndef IMAGE_H_
#define IMAGE_H_

#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"
#include "Transform.h"

class Image : public Component
{
public:
	Image(Texture* t) : tex(t), tr(nullptr) {}
	virtual ~Image() {}
	void render() override;
	void initComponent() override;
	inline Texture* getTexture() { return tex; }
protected:
	Transform* tr;
	Texture* tex;
};

#endif /*IMAGE_H_*/