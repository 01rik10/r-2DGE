#include "Asteroid.h"
#include <iostream>
Asteroid::Asteroid(const glm::vec2& position, const glm::vec2& velocity) :Unit()
{
	glm::vec2* vertices = new glm::vec2[7]{
		glm::vec2(0,0),
		glm::vec2(-5,20),
		glm::vec2(10,50),
		glm::vec2(50,55),
		glm::vec2(20,40),
		glm::vec2(55,10),
		glm::vec2(20,-10)
	};
	shape = new Polygon(vertices,7);
	dynamics.position = position;
	dynamics.velocity = velocity;
	shape->setPosition(dynamics.position);
}

void Asteroid::update()
{
	dynamics.update();
	if (dynamics.position.x > 480.0f) dynamics.position.x = -480.0f;
	if (dynamics.position.x < -480.0f) dynamics.position.x = 480.0f;
	if (dynamics.position.y > 270.0f) dynamics.position.y = -270.0f;
	if (dynamics.position.y < -270.0f) dynamics.position.y = 270.0f;
	shape->setPosition(dynamics.position);
}
