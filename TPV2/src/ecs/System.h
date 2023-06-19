#ifndef SYSTEM_H_
#define SYSTEM_H_

#include "../game/ecs_def.h"
#include "../utils/Vector2D.h"
class Entity;
class Texture;
class Vector2D;

struct Message {
	ecs::msgId_type id;
	// _m_STÄRT_GAME
	struct {
	} start_game_data;
	// _m_PAUSE_GAME
	struct {
		
	} pause_game_data;
	// _m_WIN_GAME / _m_LOSE_GAME
	struct {
		bool win;
		bool pause;
	} end_game_data;
	// _m_BULLET_SHOT
	struct {
		ecs::grpId_type gId;
		Vector2D pos;
		Vector2D vel;
		Texture* bulletTexture;
		int windowWidth;
		int windowHeight;
		float width;
		float height;
		float rot;
	} shot_bullet_data;
	

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