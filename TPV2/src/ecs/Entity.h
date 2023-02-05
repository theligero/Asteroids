#ifndef ENTITY_H_
#define ENTITY_H_

#include "Component.h"
#include "../game/ecs_def.h"
#include <vector>
#include <array>

using namespace ecs;

class Entity
{
public:
	Entity();
	virtual ~Entity();
	void setContext(Manager* man);
	bool isAlive();
	void setAlive(const bool& al);
	//template <typename T, typename ...Ts>
	//inline T* addComponent(cmpId_type cId, Ts &&…args);
	void removeComponent(cmpId_type cId);
	template <typename T>
	T* getComponent(cmpId_type cId);
	bool hasComponent(cmpId_type cId);
	virtual void update();
	virtual void render();
private:
	bool alive;
	Manager* mngr;
	std::vector<Component*> currCmps;
	std::array<Component*, ecs::maxComponentId> cmps;
};

#endif /*ENTITY_H_*/