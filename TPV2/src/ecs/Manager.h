#ifndef MANAGER_H_
#define MANAGER_H_

#include "Entity.h"
#include "../game/ecs_def.h"
#include "System.h"
#include "../utils/Singleton.h"
#include <vector>

class Entity;

class System;

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

	template<typename T, typename ...Ts>
	inline T* addSystem(Ts &&... args) {
		constexpr sysId_type sId = T::id;
		removeSystem<T>();
		System* s = new T(std::forward<Ts>(args)...);
		s->setContext(this);
		s->initSystem();
		sys_[sId] = s;
		return static_cast<T*>(s);
	}

	template<typename T>
	inline T* getSystem() {
		constexpr sysId_type sId = T::id;
		return static_cast<T*>(sys_[sId]);
	}

	template<typename T>
	inline void removeSystem() {
		constexpr sysId_type sId = T::id;
		if (sys_[sId] != nullptr) {
			delete sys_[sId];
			sys_[sId] = nullptr;
		}
	}

	inline void send(const Message& m, bool delay = false) {
		
		if (!delay) {
			for (System* s : sys_) {
				if (s != nullptr)
					s->receive(m);
			}
		}
		else {
			msgs_.emplace_back(m);
		}
	}

	inline void flushMessages() {
		std::swap(msgs_, aux_msgs_);
		for (auto& m : aux_msgs_) {
			for (System* s : sys_) {
				if (s != nullptr) {
					s->receive(m);
				}
			}
		}
		aux_msgs_.clear();
	}

private:
	
	
	//std::vector<Entity*> ents_;
	std::array<std::vector<Entity*>, maxGroupId> entsByGroup_;
	std::array<System*, maxSystemId> sys_;
	std::vector<Message> msgs_;
	std::vector<Message> aux_msgs_;
};

#endif /*MANAGER_H_*/