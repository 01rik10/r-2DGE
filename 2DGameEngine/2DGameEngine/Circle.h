#pragma once
#include "Shape.h"
class Circle:public Shape
{
public:
	//constructor
	Circle(float radius, float precisionFactorRadians) :Shape(), _radius(radius), _precisionFactorRadians(precisionFactorRadians) {
		_scale = glm::scale(glm::mat4(1.0f),glm::vec3(_radius, _radius, 1.0f));
		_verticesCount = ((pi * 2.0f) / _precisionFactorRadians) * 3;
		while (++_verticesCount % 3 != 0);
		_vertices = new Vertex[_verticesCount];

		float currRad = 0;	
		for (int i = 0;i < _verticesCount;i=i+3) {
			_vertices[i] = { 0.0f,0.0f	,1.0f,1.0f,1.0f };
			_vertices[i + 1] = { sin(currRad),cos(currRad)		,1.0f,1.0f,1.0f };
			_vertices[i + 2] = { sin(currRad+precisionFactorRadians),cos(currRad+precisionFactorRadians)		,1.0f,1.0f,1.0f };
			currRad += precisionFactorRadians;
		}
	}
	//getters
	virtual float getRadius() const	{	return _radius;	}
	//collision
	virtual bool intersects(const Shape& other) { return true; }

	virtual bool isIntersecting(const Polygon& other) const { return true; }
	virtual bool isIntersecting(const Circle& other) const { return true; }
protected:
	const float pi = 3.14159265358979323846;
	float _radius;
	float _precisionFactorRadians;

};

