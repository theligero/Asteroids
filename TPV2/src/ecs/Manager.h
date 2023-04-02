#ifndef MANAGER_H_
#define MANAGER_H_

#include "Entity.h"
#include "System.h"
#include "../utils/Singleton.h"
#include <vector>

class Manager : public Singleton<Manager>
{
public:
	virtual ~Manager();

	Entity* addEntity(ecs::grpId_type gId = _grp_GENERAL);
	inline const auto& getEntities(ecs::grpId_type gId = _grp_GENERAL) { return entsByGroup_[gId]; }
	inline void setHandler(ecs::hdlrId_type hId, Entity* e) {
		hdlrs_[hId] = e;
	}
	inline Entity* getHandler(ecs::hdlrId_type hId) {
		return hdlrs_[hId];
	}
	void refresh();
	void update();
	void update(ecs::grpId_type gId);
	void render();

	template <typename T, typename ...Ts>
	inline T* addComponent(Entity *e, Ts&& ...args) {
		T* c = new T(std::forward<Ts>(args)...);

		constexpr cmpId_type cId = T::id;
		removeComponent<T>();

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
			auto iter = std::find(e->currCmps.begin(), e->currCmps.end(), e->cmps[cId]);
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
	inline bool& isAlive(Entity* e) { 
		return e->alive; 
	}
	inline void setAlive(Entity* e, bool alive) {
		e->alive = alive;
	}
	inline grpId_type groupId(Entity* e) {
		return e->gId_;
	}
	

private:
	friend Singleton<Manager>;
	Manager();
	//std::vector<Entity*> ents_;
	std::array<std::vector<Entity*>, ecs::maxGroupId> entsByGroup_;
	std::array < Entity*, maxHdlrId> hdlrs_;
	std::array < System*, maxSystemId> sys_;
};

#endif /*MANAGER_H_*/