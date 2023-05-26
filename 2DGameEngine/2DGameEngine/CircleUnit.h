#pragma once
#include "Unit.h"
#include "Circle.h"
#include "IsoTriangleUnit.h"
#include "RectengleUnit.h"
class CircleUnit:public Unit,public Circle
{
public:
	CircleUnit();
	CircleUnit(float radius, float precisionRad);
	//colision detection
	//virtual void checkCollision(Unit* other);
	//circle on circle
	//virtual void isColliding(CircleUnit* other);
	//circle on isotriangle
	//virtual void isColliding(IsoTriangleUnit* other);
	//circle on rectengle
	//virtual void isColliding(const RectengleUnit* other);
protected:
	virtual void init();
	virtual glm::mat4 getScale();
};

