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
	_grp_PAUSE,
	_LAST_GRP_ID
};

constexpr grpId_type maxGroupId = _LAST_GRP_ID;

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
private:
	
	
	//std::vector<Entity*> ents_;
	std::array<std::vector<Entity*>, maxGroupId> entsByGroup_;
};

#endif /*MANAGER_H_*/