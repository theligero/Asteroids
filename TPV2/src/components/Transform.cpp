#include "Transform.h"

void Transform::update()
{
	/*Vector2D rot(sin(rotation), cos(rotation));
	pos = pos + (Vector2D(rot.getX() * dir.getX(), rot.getY() * dir.getY()));*/

	pos = pos + dir;
}