#ifndef MANAGER_H_
#define MANAGER_H_

#include "Entity.h"
#include "../game/ecs_def.h"
#include "../utils/Singleton.h"
#include <vector>

class Entity;

class Manager : public Singleton<Manager>
{
friend Singleton<Manager>;
public:
	Manager();
	virtual ~Manager();

	Entity* addEntity(grpId_type gId = _grp_GENERAL);
	inline const auto& getEntities(grpId_type gId = _grp_GENERAL) { return entsByGroup_[gId]; }
	void refresh();
	void update();
	void update(grpId_type gId);
	void render();

	template <typename T, typename ...Ts>
	inline T* addComponent(Entity *e, Ts&& ...args) {
		T* c = new T(std::forward<Ts>(args)...);

		constexpr cmpId_type cId = T::id;

		removeComponent<T>(e);

		e->currCmps.push_back(c);
		e->cmps[cId] = c;

		c->setContext(e, this);
		c->initComponent();

		return c;
	}

	template <typename T>
	inline void removeComponent(Entity* e) {
		constexpr cmpId_type cId = T::id;
		if (e->cmps[cId] != nullptr) {
			auto it = std::find(e->currCmps.begin(), e->currCmps.end(), e->cmps[cId]);
			e->currCmps.erase(it);
			delete e->cmps[cId];
			e->cmps[cId] = nullptr;
		}
	}

	template <typename T>
	inline bool hasComponent(Entity* e) {
		constexpr cmpId_type cId = T::id;
		return e->cmps[cId] != nullptr;
	}

	template <typename T>
	inline T* getComponent(Entity* e) {
		constexpr cmpId_type cId = T::id;
		return static_cast<T*>(e->cmps[cId]);
	}
	inline void setAlive(Entity *e, const bool& al) {
		e->alive = al;
	}
	inline bool& isAlive(Entity* e) {
		return e->alive; 
	}
	inline grpId_type groupId(Entity* e) {
		return e->gId_;
	}
private:
	
	
	//std::vector<Entity*> ents_;
	std::array<std::vector<Entity*>, maxGroupId> entsByGroup_;
};

#endif /*MANAGER_H_*/