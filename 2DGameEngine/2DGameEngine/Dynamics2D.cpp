#include "Dynamics2D.h"

Dynamics2D::Dynamics2D():position(),dPosition(),velocity(),dVelocity(),acceleration(),rotation(),mass(),oneDividedByMass(),forces()
{
}

void Dynamics2D::update()
{
	//sum forces
	glm::vec2 sigmaF(0,0);
	for (glm::vec2 force : forces) {
		sigmaF += force;
	}
	acceleration = sigmaF * oneDividedByMass; // f=ma -> a = f/m
	dVelocity = velocity;
	velocity = velocity + acceleration;
	dPosition = position;
	position = position + velocity;
}
