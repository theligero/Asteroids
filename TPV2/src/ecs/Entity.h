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
	virtual ~Entity();
	void setContext(Manager* man);
	inline bool& isAlive() { return alive; }
	void setAlive(const bool& al);
	template <typename T, typename ...Ts>
	inline T* addComponent(cmpId_type cId, Ts&& ...args) {
		T* c = new T(std::forward<Ts>(args)...);

		removeComponent(cId);

		currCmps.push_back(c);
		cmps[cId] = c;

		c->setContext(this, mngr);
		c->initComponent();

		return c;
	}
	inline void removeComponent(cmpId_type cId) {
		if (cmps[cId] != nullptr) {
			auto it = std::find(currCmps.begin(), currCmps.end(), cmps[cId]);
			currCmps.erase(it);
			delete cmps[cId];
			cmps[cId] = nullptr;
		}
	}
	template <typename T>
	inline T* getComponent(cmpId_type cId) {
		return static_cast<T*>(cmps[cId]);
	}
	inline bool hasComponent(cmpId_type cId) {
		return cmps[cId] != nullptr;
	}
	inline virtual void update();
	inline virtual void render();

private:
	bool alive;
	Manager* mngr;
	std::vector<Component*> currCmps;
	std::array<Component*, ecs::maxComponentId> cmps;
};

#endif /*ENTITY_H_*/