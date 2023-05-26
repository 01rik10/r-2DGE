#pragma once
#include "Shape.h"
class Rectengle:public Shape
{
public:
	//constructor
	Rectengle(float width, float height) :Shape(), _width(width), _height(height), _halfWidth(width / 2.0f), _halfHeight(height / 2.0f) {
		_scale = glm::scale(glm::mat4(1.0f), glm::vec3(_halfWidth, _halfHeight, 1.0f));
		_verticesCount = 6;
		_vertices = new Vertex[_verticesCount]{
				{-1.0f,-1.0f	,1.0f,1.0f,1.0f},
				{-1.0f,1.0f		,1.0f,1.0f,1.0f},
				{1.0f,-1.0f		,1.0f,1.0f,1.0f},
				{1.0f,1.0f		,1.0f,1.0f,1.0f},
				{1.0f,-1.0f		,1.0f,1.0f,1.0f},
				{-1.0f,1.0f		,1.0f,1.0f,1.0f}
		};
	}
	//getters
	virtual float getWidth() { return _width; }
	virtual float getHeight() { return _height; }

	virtual bool intersects(const Shape& other) { return true; }

	virtual bool isIntersecting(const Polygon& other) const { return true; }
	virtual bool isIntersecting(const Circle& other) const { return true; }
protected:
	float _width;
	float _height;
	float _halfWidth;
	float _halfHeight;
	void init() {
	}
};

