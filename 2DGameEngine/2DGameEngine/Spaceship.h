#pragma once
#include "Unit.h"
#include "Polygon.h"
class Spaceship:public Unit
{
public:
	Spaceship();
	void rotateLeft();
	void rotateRight();
	void accelerate();
	void stopAccelerate();
	void update();
private:
	bool _canAddForce;
	float _frictionConst;
};

