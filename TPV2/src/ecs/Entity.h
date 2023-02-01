#ifndef ENTITY_H_
#define ENTITY_H_

#include <vector>
#include "Manager.h"

class Component;

class Manager;

class Entity
{
public:
	Entity();
	virtual ~Entity();
	inline bool isAlive();
	inline void setAlive(const bool& al);
	template <typename T, typename ...Ts>
	inline T* addComponent();
	inline void deleteComponent();
	template <typename T>
	inline T* getComponent();
	inline bool hasComponent();
	virtual void update();
	virtual void render();
private:
	bool alive;
	Manager* mngr;
	std::vector<Component*> currCmps;
	// std::array<Component*> cmps;
};

#endif /*ENTITY_H_*/