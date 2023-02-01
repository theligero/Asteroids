#ifndef COMPONENT_H_
#define COMPONENT_H_

#include "Entity.h"

class Component
{
public:
	Component();
	virtual ~Component();
	inline void setContext(Entity* e, Manager* m);

	virtual void update();
	virtual void render();
	virtual void handleEvents() {}
protected:
	Entity* ent;
	Manager* mngr;
};

#endif /*COMPONENT_H_*/