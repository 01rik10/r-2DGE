#include "IsoTriangleUnit.h"

IsoTriangleUnit::IsoTriangleUnit() :Unit(), IsoTriangle(1.0f, 1.0f)
{
	init();
}

IsoTriangleUnit::IsoTriangleUnit(float width, float height):Unit(), IsoTriangle(width,height)
{
	init();
}

void IsoTriangleUnit::checkCollision(Unit* other)
{
	//other->checkCollision(*this);
}

void IsoTriangleUnit::init()
{
	//vertices->push_back({ 0.0f, 1.0f		,1.0f, 0.0f, 0.5f });
	//vertices->push_back({ 1.0f,-1.0f		,1.0f, 0.5f, 1.0f });
	//vertices->push_back({ -1.0f,-1.0f		,1.0f, 0.0f, 1.0f });
}

glm::mat4 IsoTriangleUnit::getScale()
{
	return glm::mat4(1.0f);
}

