#pragma once
#include "Unit.h"
#include "Rectengle.h"
class RectengleUnit:public Unit,public Rectengle
{
public:
	RectengleUnit();
	RectengleUnit(float width, float height);
	virtual void setRectengle(float width, float height);
protected:
	virtual void init();
	virtual glm::mat4 getScale();
};

