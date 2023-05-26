#include "CircleUnit.h"


#include <cmath>
#include "Camera2D.h"
#include <glm/glm.hpp>
CircleUnit::CircleUnit() :Unit(), Circle(1.0f, 0.2f)
{
	init();
}

CircleUnit::CircleUnit(float radius, float precisionRad) :Unit(), Circle(radius, precisionRad)
{
	init();
}

//void CircleUnit::checkCollision(Unit* other)
//{
	//other->isColliding(this);
//}

//void CircleUnit::isColliding(CircleUnit* other)
//{
	
//}

//void CircleUnit::isColliding(IsoTriangleUnit* other)
//{
	//glm::vec2 centerToCenter = dynamics.position - other.getPosition();
//}

void CircleUnit::init()
{
	std::vector<Shape::Vertex> vertices;
	float currRad = 0.0f;
	while (currRad < pi * 2) {
		vertices.push_back({ 0.0f,0.0f,0.5f,0.5f,0.5f });
		vertices.push_back({ sin(currRad), cos(currRad),0.5f,0.5f,0.5f });
		vertices.push_back({ sin(currRad + _precisionFactorRadians), cos(currRad + _precisionFactorRadians),0.5f,0.5f,0.5f });
		currRad = currRad + _precisionFactorRadians;
	}
	std::cout << "circle num vertices " << vertices.size() << std::endl;
}

glm::mat4 CircleUnit::getScale()
{
	return glm::mat4(1.0f);
}
