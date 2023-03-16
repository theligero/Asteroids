#ifndef ENTITY_H_
#define ENTITY_H_

#include "Component.h"
#include "../game/ecs_def.h"
#include <vector>
#include <array>
#include <bitset>

using namespace ecs;

class Entity
{
public:
	Entity(grpId_type gId);
	Entity(const Entity&) = delete;
	Entity& operator = (const Entity&) = delete;
	virtual ~Entity();
	void setContext(Manager* man);
	inline bool& isAlive() { return alive; }
	inline virtual void update();
	inline virtual void render();

private:
	friend Manager;
	
	bool alive;
	Manager* mngr;
	std::vector<Component*> currCmps;
	std::array<Component*, ecs::maxComponentId> cmps;
	grpId_type gId_;
};

#endif /*ENTITY_H_*/