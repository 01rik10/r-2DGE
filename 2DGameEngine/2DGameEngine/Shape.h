#pragma once
#include <glm/gtc/matrix_transform.hpp>
#include "Line2D.h"
class Circle;
class Polygon;
class Shape
{
public:
	struct Vertex {
		float pos[2];
		float color[3];
	};
	//getters
	virtual int getVerticesCount() { return _verticesCount; }
	virtual Vertex* getVertices() { return _vertices; }
	virtual glm::vec2 getPosition() const { return _position; }
	virtual float getRotation() { return _rotationAngle; }
	virtual glm::mat4 getModelMatrix() const;
	//setters
	virtual void setPosition(glm::vec2 position);
	virtual void setRotation(float rotation);
	//intersection
	virtual bool intersects(const Shape& other) = 0;

	virtual bool isIntersecting(const Polygon& other) const = 0;
	virtual bool isIntersecting(const Circle& other) const = 0;
protected:
	//vertices container
	int _verticesCount;
	Vertex* _vertices;

	//shape world information
	glm::vec2 _position = glm::vec2(0.0f,0.0f);
	float _rotationAngle = 0.0f;

	//model matrices
	glm::mat4 _translation = glm::mat4(1.0f);
	glm::mat4 _rotation = glm::mat4(1.0f);
	glm::mat4 _scale = glm::mat4(1.0f);

	//shape normalized init
	//virtual void init() = 0;
};

