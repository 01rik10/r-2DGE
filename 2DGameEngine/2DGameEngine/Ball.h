#pragma once
#include "CircleUnit.h"
#include <glm/glm.hpp>
class Ball:public CircleUnit
{
public:
	Ball();
	void move();
	void collide();
};

