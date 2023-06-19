#ifndef HEALTH_H_
#define HEALTH_H_

#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"
#include "Transform.h"

const int MAX_LIVES = 3;
const int MIN_LIVES = 3;


struct Health : public Component
{
private:
	int livesCount = MAX_LIVES;
	int window_Width, window_Height;
	Texture* tex;
	Transform* tr;
public:
	constexpr static cmpId_type id = ecs::HEALTH;
	Health(int w, int h, Texture* t) : window_Width(w), window_Height(h), tex(t) {}
	int getLives() { return livesCount; }
	void decreaseLives();
	inline Texture* getTexture() { return tex; }
	void resetLives() { livesCount = MAX_LIVES; }
	//void render() override;
	void initComponent() override;
};

#endif /*HEALTH_H_*/