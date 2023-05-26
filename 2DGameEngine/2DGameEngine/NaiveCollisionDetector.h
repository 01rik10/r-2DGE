#pragma once
#include "Unit.h"
#include <vector>
#include "CollisionSolver.h"
class NaiveCollisionDetector
{
public:
	NaiveCollisionDetector() :_cs() {}
	void checkCollisions(std::vector<Unit*> units);
private:
	CollisionSolver _cs;
};

