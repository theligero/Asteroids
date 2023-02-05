#include "Transform.h"

Vector2D& Transform::getPos()
{
	return pos;
}

Vector2D& Transform::getDir()
{
	return dir;
}

float& Transform::getW()
{
	return width;
}

float& Transform::getH()
{
	return height;
}

float& Transform::getRot()
{
	return rotation;
}

void Transform::update()
{
	pos = pos + dir;
}
