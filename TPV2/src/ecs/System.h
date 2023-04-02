#ifndef SYSTEM_H_
#define SYSTEM_H_

#include "../game/ecs_def.h"

struct Message {
	ecs::msgId_type id;
	// _m_STAR_EATEN
	struct {
		Entity* e;
	} star_eaten_data;
	// _m_ADD_STARS
	struct {
		unsigned int n;
	} add_stars_data;
};

class Manager;

class System {
public:
	virtual ~System() {}
	void setContext(Manager* mngr) {
		man = mngr;
	}
	virtual void initSystem() {}
	virtual void update() {}
	virtual void receive(const Message& m) {}
protected:
	Manager* man;
};

#endif /*SYSTEM_H_*/