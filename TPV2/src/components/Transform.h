#ifndef TRANSFORM_H_
#define TRANSFORM_H_

#include "../ecs/Component.h"
#include "../utils/Vector2D.h"

class Transform : public Component 
{
public:
	Transform(Vector2D p, Vector2D d, float w, float h, float r) : 
		pos(p), dir(d), width(w), height(h), rotation(r) {}
	virtual ~Transform() {}
	inline Vector2D& getPos() { return pos; }
	inline Vector2D& getDir() { return dir; }
	float& getW();
	float& getH();
	float& getRot();

	void update() override;
private:
	Vector2D pos;
	Vector2D dir;
	float width;
	float height;
	float rotation;
};

#endif /*TRANSFORM_H_*/