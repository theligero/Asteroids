#include "FramedImage.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"

void FramedImage::initComponent()
{
	tr = mngr->getComponent<Transform>(ent);
	assert(tr != nullptr);
}
