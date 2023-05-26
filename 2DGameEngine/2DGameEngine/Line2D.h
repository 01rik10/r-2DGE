#pragma once
#include <glm/glm.hpp>
#include <cmath>
class Line2D {
public:
	struct LineIntersection {
		bool isIntersecting;
		glm::vec2 intersectionPoint;
	};
	Line2D(const glm::vec2& p1, const glm::vec2& p2) {
		slope = (p2.y - p1.y) / (p2.x - p1.x);
		intercept = p1.y - slope * p1.x;
		if (p1.x > p2.x) {
			leftLimit = p2.x;
			rightLimit = p1.x;
		}
		else {
			leftLimit = p1.x;
			rightLimit = p2.x;
		}
	}
	LineIntersection isIntersecting(const Line2D& other) {
		if (slope == other.slope) return { false,glm::vec2(0,0) };
		bool onLimit;
		float x;
		float y;
		x =  (other.intercept - intercept)/ (slope - other.slope);
		onLimit = ((x >= std::fmax(leftLimit, other.leftLimit)) && 
			(x <= std::fmin(rightLimit, other.rightLimit)));
		if (!onLimit) return { false,glm::vec2(0,0) };
		else return { true,glm::vec2(x,slope * x + intercept) };
	}
	float slope;
	float intercept;
	float leftLimit;
	float rightLimit;
};