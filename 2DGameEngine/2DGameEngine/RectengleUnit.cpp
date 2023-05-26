#include "RectengleUnit.h"

RectengleUnit::RectengleUnit():Unit(),Rectengle(1.0f,1.0f)
{
	init();
}

RectengleUnit::RectengleUnit(float width, float height) :Unit(), Rectengle(width, height)
{
	init();
}

void RectengleUnit::setRectengle(float width, float height)
{
	//setWidth(width);
	//setHeight(height);
	//updateScale(glm::vec3(_halfWidth, _halfHeight, 1.0f));
}

glm::mat4 RectengleUnit::getScale()
{
	return glm::mat4(1.0f);
}

void RectengleUnit::init()
{
	//vertices->push_back({ -1.0f,-1.0f		,1.0f,1.0f,1.0f });
	//vertices->push_back({ -1.0f,1.0f		,1.0f,1.0f,1.0f });
	//vertices->push_back({ 1.0f,-1.0f		,1.0f,1.0f,1.0f });
	//vertices->push_back({ 1.0f,1.0f			,1.0f,1.0f,1.0f });
	//vertices->push_back({ 1.0f,-1.0f		,1.0f,1.0f,1.0f });
	//vertices->push_back({ -1.0f,1.0f		,1.0f,1.0f,1.0f });
}
