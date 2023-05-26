#pragma once
#include "Shape.h"

//simple polygon with no holes
class Polygon : public Shape {
public:
	Polygon(glm::vec2* vertices, int numVertices);
	int getNumEdges() const { return _borderEdgesCount; }
	glm::mat2* getBorder() const { return _borders; }
	virtual bool intersects(const Shape& other);

	virtual bool isIntersecting(const Polygon& other) const;
	virtual bool isIntersecting(const Circle& other) const;

protected:
	const float pi = 3.14159265358979323846;
	float _area;
	glm::vec2 centroid;
	glm::mat2* _borders;
	int _borderEdgesCount;
	//calculates b angle given 3 points
	float calculateAngle(const glm::vec2& a, const glm::vec2& b, const glm::vec2& c) {
		//find vec ba bc
		glm::vec2 ba = a - b;
		glm::vec2 bc = c - b;
		return acosf((glm::dot(ba, bc)) / (glm::length(ba) + glm::length(bc)));
	}
	//checks <abc orientation
	bool isClockWise(const glm::vec2& a, const glm::vec2& b, const glm::vec2& c) {
		return glm::determinant(glm::mat3(
			glm::vec3(a, 1.0f),
			glm::vec3(b, 1.0f),
			glm::vec3(c, 1.0f)
		)) < 0;
	}
	int clampIndex(int x, int a, int b) {
		if (x > b) return a;
		if (x < a) return b;
		else return x;
	}
};
