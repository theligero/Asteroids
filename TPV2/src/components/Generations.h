#ifndef GENERATIONS_H_
#define GENERATIONS_H_

#include "../ecs/Component.h"
#include "../game/ecs_def.h"

using namespace ecs;

const int MAX_GENERATIONS = 3;
const int MIN_GENERATIONS = 1;

struct Generations : public Component
{
public:
	constexpr static cmpId_type id = GENERATIONS;
	Generations(int newGenerations) : generationsLeft(newGenerations){ }
	virtual ~Generations() { }

	inline void nextGeneration() { --generationsLeft; }
	inline int getGenerations() { return generationsLeft; }

private:
	int generationsLeft;

};

#endif /*GENERATIONS_H_*/