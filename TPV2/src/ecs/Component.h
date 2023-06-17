#ifndef COMPONENT_H_
#define COMPONENT_H_



class Entity;

class Manager;

struct Component
{
public:
	Component() : ent(), mngr() {}
	virtual ~Component() {}
	inline void setContext(Entity* e, Manager* m) {
		ent = e;
		mngr = m;
	}

	virtual void update() {}
	virtual void render() {}
	virtual void initComponent() {}
protected:
	Entity* ent;
	Manager* mngr;
};

#endif /*COMPONENT_H_*/