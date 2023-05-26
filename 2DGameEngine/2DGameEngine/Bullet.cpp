#include "Bullet.h"

Bullet::Bullet(float direction,glm::vec2 shotFrom):CircleUnit(4.0f,0.2f)
{
	dynamics.position = shotFrom;
	dynamics.velocity.x = 10 * sin(direction);
	dynamics.velocity.y = 10 * cos(direction);
}

void Bullet::update()
{
	dynamics.update();
	//if (dynamics.position.x < -480 || dynamics.position.x>480 || dynamics.position.y > 270 || dynamics.position.y < -270) expired = true;
}
