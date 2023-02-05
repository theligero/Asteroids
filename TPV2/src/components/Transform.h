#ifndef TRANSFORM_H_
#define TRANSFORM_H_

#include "../ecs/Component.h"
#include "../utils/Vector2D.h"

class Transform : public Component 
{
public:
	Transform(float w, float h, float r) : width(w), height(h), rotation(r) {}
	virtual ~Transform() {}
	Vector2D& getPos();
	Vector2D& getDir();
	float& getW();
	float& getH();
	float& getRot();

	void update();
private:
	Vector2D pos;
	Vector2D dir;
	float width;
	float height;
	float rotation;
};

#endif /*TRANSFORM_H_*/