#pragma once
#include "CircleUnit.h"
class Bullet:public CircleUnit
{
public:
	Bullet(float direction,glm::vec2 shotFrom);
	void update();
};

