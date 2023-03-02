#ifndef HEALTH_H_
#define HEALTH_H_

#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"
#include "Transform.h"

const int MAX_LIVES = 3;

class Health : public Component
{
private:
	int livesCount = MAX_LIVES;
	int window_Width, window_Height;
	Texture* tex;
	Transform* tr;
public:
	Health(int w, int h, Texture* t) : window_Width(w), window_Height(h), tex(t) {}
	int getLives() { return livesCount; }
	void decreaseLives();
	void resetLives() { livesCount = MAX_LIVES; }
	void render() override;
	void initComponent() override;
};

#endif /*HEALTH_H_*/