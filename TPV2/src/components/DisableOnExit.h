#ifndef DISABLE_ON_EXIT_H_
#define DISABLE_ON_EXIT_H_

#include "../ecs/Component.h"
#include "Transform.h"

class DisableOnExit : public Component
{
public:
	DisableOnExit();
	virtual ~DisableOnExit() {}

	void update() override;
private:
	Transform* tr;
	float widthTr;
	float heightTr;
};

#endif /*DISABLE_ON_EXIT_H_*/