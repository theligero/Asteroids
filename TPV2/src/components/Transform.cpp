#include "Transform.h"

inline Vector2D& Transform::getPos()
{
	return pos;
}

inline Vector2D& Transform::getDir()
{
	return dir;
}

inline float& Transform::getW()
{
	return width;
}

inline float& Transform::getH()
{
	return height;
}

inline float& Transform::getRot()
{
	return rotation;
}

void Transform::update()
{
	pos = pos + dir;
}
