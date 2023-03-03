#ifndef MANAGER_H_
#define MANAGER_H_

#include "Entity.h"
#include "../utils/Singleton.h"
#include <vector>

using grpId_type = uint8_t;
enum grpId : grpId_type {
	_grp_GENERAL,
	_grp_ASTEROIDS,
	_grp_BULLETS,
	_LAST_GRP_ID
};

constexpr grpId_type maxGroupId = _LAST_GRP_ID;

class Manager : public Singleton<Manager>
{
public:
	virtual ~Manager();

	Entity* addEntity(grpId_type gId = _grp_GENERAL);
	inline const auto& getEntities(grpId_type gId = _grp_GENERAL) { return entsByGroup_[gId]; }
	void refresh();
	void update();
	void render();
	inline const auto& getEntitiesByGroup(grpId_type gId) {
		return entsByGroup_[gId];
	}
	inline void addToGroupList(grpId_type gId, Entity* e) {
		entsByGroup_[gId].push_back(e);
	}

private:
	friend Singleton<Manager>;
	Manager();
	//std::vector<Entity*> ents_;
	std::array<std::vector<Entity*>, maxGroupId> entsByGroup_;
};

#endif /*MANAGER_H_*/