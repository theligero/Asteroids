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
	inline void setPos(const Vector2D& p) { pos = p; }
	inline Vector2D& getDir() { return dir; }
	inline Vector2D& getCenter() { return center; }
	inline float& getRot() { return rotation; }
	inline void setRot(float rot) { rotation = rot; }
	inline float& getW() { return width; }
	inline float& getH() { return height; }

	void initComponent() override;
	void update() override;
private:
	Vector2D pos;
	Vector2D dir;
	Vector2D center;
	float width;
	float height;
	float rotation;
};

#endif /*TRANSFORM_H_*/