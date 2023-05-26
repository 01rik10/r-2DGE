#pragma once
#include "Unit.h";
#include "IsoTriangle.h"
class IsoTriangleUnit:public Unit,public IsoTriangle
{
public:
	IsoTriangleUnit();
	IsoTriangleUnit(float width, float height);
	virtual void checkCollision(Unit* other);
protected:
	virtual void init();
	virtual glm::mat4 getScale();
};

