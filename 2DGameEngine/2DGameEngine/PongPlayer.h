#pragma once
#include "RectengleUnit.h"
#include "Time.h"
class PongPlayer:public RectengleUnit
{
public:
	PongPlayer();
	void moveRight();
	void moveLeft();
};

