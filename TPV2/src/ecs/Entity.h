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
	Entity();
	Entity(ecs::grpId_type gId);
	Entity(const Entity&) = delete;
	Entity& operator=(const Entity&) = delete;
	virtual ~Entity();
	void setContext(Manager* man);
	inline bool& isAlive() { return alive; }
	inline virtual void update();
	inline virtual void render();

private:
#ifndef PARTE_2
	Manager* mngr;
#else
	friend Manager;
#endif
	std::vector<Component*> currCmps;
	std::array<Component*, ecs::maxComponentId> cmps;
	bool alive;
	ecs::grpId_type gId;
};

#endif /*ENTITY_H_*/