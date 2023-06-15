#ifndef GENERATIONS_H_
#define GENERATIONS_H_

#include "../ecs/Component.h"

const int MAX_GENERATIONS = 3;
const int MIN_GENERATIONS = 1;

class Generations : public Component
{
public:
	Generations(int newGenerations) : generationsLeft(newGenerations){ }
	virtual ~Generations() { }

	inline void nextGeneration() { --generationsLeft; }
	inline int getGenerations() { return generationsLeft; }

private:
	int generationsLeft;

};

#endif /*GENERATIONS_H_*/