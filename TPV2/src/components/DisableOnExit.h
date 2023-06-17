#ifndef DISABLE_ON_EXIT_H_
#define DISABLE_ON_EXIT_H_

#include "../ecs/Component.h"
#include "Transform.h"

class DisableOnExit : public Component
{
public:
	constexpr static cmpId_type id = DISABLE_ON_EXIT;
	DisableOnExit(int w, int h) : WindowWidth(w), WindowHeight(h) {}
	virtual ~DisableOnExit() {}

	void initComponent() override;
	void update() override;
private:
	Transform* tr = nullptr;
	int WindowWidth;
	int WindowHeight;
};

#endif /*DISABLE_ON_EXIT_H_*/