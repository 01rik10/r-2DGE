#include "PongPlayer.h"



PongPlayer::PongPlayer():RectengleUnit()
{
}

void PongPlayer::moveRight()
{
	float move = dynamics.position.x + 0.5f*Time::getDeltaTime();
	if (move < 1.0f - _width);
		//initPos(move, dynamics.position.y);
}

void PongPlayer::moveLeft()
{
	float move = dynamics.position.x - 0.5f*Time::getDeltaTime();
	if (move >= -1.0f);
		//initPos(move, dynamics.position.y);
}
