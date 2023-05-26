#include "Ball.h"
#include <iostream>
Ball::Ball() :CircleUnit()
{
	dynamics.velocity.x = 0.005f;
	dynamics.velocity.y = -0.01f;
}

void Ball::move()
{
	dynamics.position.x += dynamics.velocity.x;
	dynamics.position.y += dynamics.velocity.y;
	if (dynamics.position.x < -1.0f || dynamics.position.x>1.0f) dynamics.velocity.x *= -1;
	//if (dynamics.position.y < -1.0f || dynamics.position.y>1.0f) dynamics.velocity.y *= -1;
}

void Ball::collide()
{
	dynamics.velocity.y *= -1;
}


