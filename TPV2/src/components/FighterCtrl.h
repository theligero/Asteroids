#ifndef FIGHTER_CTRL_H_
#define FIGHTER_CTRL_H_

#include "../ecs/Component.h"
#include "../sdlutils/InputHandler.h"
#include "Transform.h"

class FighterCtrl : public Component
{
public:
	FighterCtrl() : tr(nullptr) { InputHandler::init(); }
	virtual ~FighterCtrl() { InputHandler::close(); }

	void initComponent() override;
	void update() override;
private:
	Transform* tr;
};

#endif /*FIGHTER_CTRL_H_*/