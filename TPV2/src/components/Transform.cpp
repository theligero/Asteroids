#include "Transform.h"

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