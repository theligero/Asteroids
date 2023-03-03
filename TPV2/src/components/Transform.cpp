#include "Transform.h"

void Transform::initComponent()
{
	center = pos + Vector2D(width / 2.0f, height / 2.0f);
}

void Transform::update()
{
	pos = pos + dir;
	center = pos + Vector2D(width / 2.0f, height / 2.0f);
}