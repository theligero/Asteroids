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
	inline T* addComponent(Ts&& ...args) {
		T* c = new T(std::forward<Ts>(args)...);

		constexpr cmpId_type cId = T::id;

		removeComponent<T>();

		currCmps.push_back(c);
		cmps[cId] = c;

		c->setContext(this, mngr);
		c->initComponent();

		return c;
	}
	template <typename T>
	inline void removeComponent() {
		constexpr cmpId_type cId = T::id;
		if (cmps[cId] != nullptr) {
			auto it = std::find(currCmps.begin(), currCmps.end(), cmps[cId]);
			currCmps.erase(it);
			delete cmps[cId];
			cmps[cId] = nullptr;
		}
	}
	template <typename T>
	inline T* getComponent() {
		constexpr cmpId_type cId = T::id;
		return static_cast<T*>(cmps[cId]);
	}
	template <typename T>
	inline bool hasComponent() {
		constexpr cmpId_type cId = T::id;
		return cmps[cId] != nullptr;
	}
	void update();
	void render();

private:
	bool alive;
	Manager* mngr;
	std::vector<Component*> currCmps;
	std::array<Component*, ecs::maxComponentId> cmps;
};

#endif /*ENTITY_H_*/