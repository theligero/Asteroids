#ifndef DISABLE_ON_EXIT_H_
#define DISABLE_ON_EXIT_H_

#include "../ecs/Component.h"
#include "Transform.h"

class DisableOnExit : public Component
{
public:
	DisableOnExit() {}
	virtual ~DisableOnExit() {}

	void initComponent() override;
	void update() override;
private:
	Transform* tr = nullptr;
	float widthTr = 0;
	float heightTr = 0;
};

#endif /*DISABLE_ON_EXIT_H_*/