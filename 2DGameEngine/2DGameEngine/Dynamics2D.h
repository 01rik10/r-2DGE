#pragma once
#include <glm/glm.hpp>
#include <vector>;
class Dynamics2D
{
public:
	Dynamics2D();
	glm::vec2 position;
	glm::vec2 dPosition;
	glm::vec2 velocity;
	glm::vec2 dVelocity;
	glm::vec2 acceleration;
	float rotation;
	float mass;
	float oneDividedByMass;
	std::vector<glm::vec2> forces;
	void update();
};

