#ifndef SYSTEM_H_
#define SYSTEM_H_

class Message;

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