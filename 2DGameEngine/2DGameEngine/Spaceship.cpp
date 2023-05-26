#include "Spaceship.h"
#include <iostream>
Spaceship::Spaceship() :Unit(), _canAddForce(true), _frictionConst(-0.5f)
{
	glm::vec2* pverts = new glm::vec2[4]{
		glm::vec2(-10.0f,-20.0f),
		glm::vec2(0.0f,-15.0f),
		glm::vec2(10.0,-20.0f),
		glm::vec2(0.0f,20.0f)
	};
	shape = new Polygon(pverts, 4);
	//friction - keep always at loc0
	dynamics.mass = 100.0f;
	dynamics.oneDividedByMass = 1.0f / 100.0f;
	dynamics.forces.push_back(glm::vec2(0.0f, 0.0f));
}

void Spaceship::rotateLeft()
{
	dynamics.rotation -= 0.1f;
	shape->setRotation(dynamics.rotation);
}

void Spaceship::rotateRight()
{
	dynamics.rotation += 0.1f;
	shape->setRotation(dynamics.rotation);
}

void Spaceship::accelerate()
{
	if (_canAddForce) {
		dynamics.forces.push_back(glm::vec2(20*sin(dynamics.rotation), 20*cos(dynamics.rotation)));
		_canAddForce = false;
	}
}

void Spaceship::stopAccelerate()
{
	if (dynamics.forces.size() > 1) {
		dynamics.forces.pop_back();
		_canAddForce = true;
	}
}

void Spaceship::update()
{
	//update dynamics
	dynamics.update();
	//check position invariants
	if (dynamics.position.x > 480.0f) dynamics.position.x = -480.0f;
	if (dynamics.position.x < -480.0f) dynamics.position.x = 480.0f;
	if (dynamics.position.y > 270.0f) dynamics.position.y = -270.0f;
	if (dynamics.position.y < -270.0f) dynamics.position.y = 270.0f;
	shape->setPosition(dynamics.position);
	//check velocity invariants
	float velocityMagnitude = dynamics.velocity.x * dynamics.velocity.x + dynamics.velocity.y * dynamics.velocity.y;
	if ((velocityMagnitude) > 100.0f) dynamics.velocity = dynamics.dVelocity;
	//if ((velocityMagnitude) < 0.01) {
		//dynamics.velocity.x = 0.0f;
		//dynamics.velocity.y = 0.0f;
	//}
	//friction
	dynamics.forces.at(0).x = dynamics.velocity.x * _frictionConst;
	dynamics.forces.at(0).y = dynamics.velocity.y * _frictionConst;
}
