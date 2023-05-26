#pragma once
#include "Unit.h"
#include "Polygon.h"
#include "Tools.h"
#include <cstdlib>
class Asteroid :public Unit
{
public:
	Asteroid(const glm::vec2& position,const glm::vec2& velocity);
	void update();
};

