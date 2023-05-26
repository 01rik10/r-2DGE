#pragma once
#include "Sprite.h"
class AffectedByGravitySprite:public Sprite
{
public:
	void freeFall();
protected:
	bool _isFalling;
};

