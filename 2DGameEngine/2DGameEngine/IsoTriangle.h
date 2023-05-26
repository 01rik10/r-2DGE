#pragma once
#include "Shape.h"
class IsoTriangle :public Shape {
public:
	IsoTriangle(float width, float height):Shape(),_width(width),_height(height),_halfWidth(width/2.0f),_halfHeight(height/2.0f) {
		_scale = glm::scale(glm::mat4(1.0f), glm::vec3(_halfWidth, _halfHeight, 1.0f));
		_verticesCount = 3;
		_vertices = new Vertex[_verticesCount]{
			{ 0.0f, 1.0f		,1.0f, 0.0f, 0.5f },
			{ 1.0f,-1.0f		,1.0f, 0.5f, 1.0f },
			{ -1.0f,-1.0f		,1.0f, 0.0f, 1.0f }
		};
	}

	//getters
	float getWidth() const{ return _width; }
	float getHeight() const{ return _height; }
	virtual bool intersects(const Shape& other) { return true; }

	virtual bool isIntersecting(const Polygon& other) const { return true; }
	virtual bool isIntersecting(const Circle& other) const { return true; }
protected:
	float _width;
	float _height;
	float _halfWidth;
	float _halfHeight;
};