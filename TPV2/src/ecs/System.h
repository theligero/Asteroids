#ifndef SYSTEM_H_
#define SYSTEM_H_

#include "../game/ecs_def.h"
#include "../utils/Vector2D.h"
class Entity;
class Texture;
class Vector2D;
class Health;

struct Message {
	ecs::msgId_type id;
	// _m_ST�RT_GAME
	struct {
		bool pause;
		bool soloOrCoop;
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
		Vector2D pos;
		Vector2D vel;
		float width;
		float height;
		float rot;
	} shot_bullet_data;
	// _m_ASTEROID_DESTROYED
	struct {
		Entity* bulletHit;
		Entity* asteroidHit;
	} asteroid_collision_data;
	// _m_FIGHTER_HIT
	struct {
		Health* fighterHealth;
	}fighter_hit_data;
	// _m_FIGHTER_BULLET_HIT
	struct {
		Entity* bulletHit;
	}fighter_bullet_hit_data;
	// IS_m_IS_HOST  || _m_IS_GUEST
	struct {
		bool host;
		std::string name;
	}online_init_data;
	// _m_MOVE_ENEMY
	struct {
		Vector2D enemyPos;
		Vector2D enemyDir;
		float enemyRot;
	}move_enemy_data;
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