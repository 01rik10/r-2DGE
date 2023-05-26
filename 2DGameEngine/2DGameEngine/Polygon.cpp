#include "Polygon.h"
#include "Circle.h"
#include <iostream>
Polygon::Polygon(glm::vec2* vertices,int numVertices) :Shape() {
	//calculate center
	int maxX = vertices[0].x;
	int maxY = vertices[0].y;
	int minX = vertices[0].x;
	int minY = vertices[0].y;
	int rightMostPointIndex = -1;
	for (int i = 1;i < numVertices;i++) {
		if (maxX > vertices[i].x) {
			maxX = vertices[i].x;
			rightMostPointIndex = i;
		}
		if (maxY > vertices[i].y)	maxY = vertices[i].y;
		if (minX < vertices[i].x)	minX = vertices[i].x;
		if (minY < vertices[i].y)	minY = vertices[i].y;
	}
	_position = glm::vec2((maxX + minX) / 2.0f, ((maxY + minY) / 2.0f));
	//move the polygon to (0,0) - save center as translation and find scale factor
	_translation = glm::translate(glm::mat4(1.0f), glm::vec3(_position, 0.0f));
	float scaleFactor = 0;
	for (int i = 0; i < numVertices;i++) {
		vertices[i] = vertices[i] - _position;
		float checkX = std::abs(vertices[i].x);
		float checkY = std::abs(vertices[i].y);
		if (checkX > scaleFactor) scaleFactor = checkX;
		if (checkY > scaleFactor) scaleFactor = checkY;
	}
	_scale = glm::scale(glm::mat4(1.0f), glm::vec3(scaleFactor, scaleFactor, 1.0f));
	//determine border edges
	_borders = new glm::mat2[numVertices];
	for (int i = 0;i < numVertices;i++) {
		_borders[i] = glm::mat2(vertices[i] / scaleFactor, vertices[(i + 1) % numVertices] / scaleFactor);
	}
	_borderEdgesCount = numVertices;
	//triangulate - ear clipping
	//1. check polygon orientation
	bool isPolygonClockWise = isClockWise(
		vertices[clampIndex(rightMostPointIndex - 1, 0, numVertices - 1)],
		vertices[rightMostPointIndex],
		vertices[clampIndex(rightMostPointIndex + 1, 0, numVertices - 1)]
	);
	//2. calculate angles numAngles=numVertices
	float* angles = new float[numVertices];
	for (int i = 0;i < numVertices;i++) {
		float angle = calculateAngle(vertices[i], vertices[(i + 1) % numVertices], vertices[(i + 2) % numVertices]);
		bool isABCClockWise = isClockWise(vertices[i], vertices[(i + 1) % numVertices], vertices[(i + 2) % numVertices]);
		if (isABCClockWise != isPolygonClockWise) {
			angle = 2 * pi - angle;
		}
		angles[i] = angle;
	}
	struct Triangle { glm::vec2 a; glm::vec2 b; glm::vec2 c; };
	Triangle* triangles = new Triangle[numVertices - 2];
	int currNumVertices = numVertices;
	for (int i = 0;i < numVertices - 2;i++) {
		float minAngle = 10; //bigger than 2pi
		int minAngleIndex = 0;
		//first find the min angle and its index
		for (int j = 0;j < currNumVertices;j++) {
			if (angles[j] < minAngle) {
				minAngle = angles[j];
				minAngleIndex = j;
			}
		}
		//add this ear to triangles
		int prevVertexIndex = clampIndex(minAngleIndex - 1, 0, currNumVertices - 1);
		int nextVertexIndex = clampIndex(minAngleIndex + 1, 0, currNumVertices - 1);
		triangles[i] = {
			vertices[prevVertexIndex] / scaleFactor,
			vertices[minAngleIndex] / scaleFactor,
			vertices[nextVertexIndex] / scaleFactor
		};
		//calculate new formed angles
		angles[prevVertexIndex] = calculateAngle(
			vertices[clampIndex(prevVertexIndex - 1, 0, currNumVertices - 1)],
			vertices[prevVertexIndex],
			vertices[nextVertexIndex]
		);
		if (isClockWise(vertices[clampIndex(prevVertexIndex - 1, 0, currNumVertices - 1)],
			vertices[prevVertexIndex],
			vertices[nextVertexIndex])
			!= isPolygonClockWise)
			angles[prevVertexIndex] = 2.0f * pi - angles[prevVertexIndex];

		angles[nextVertexIndex] = calculateAngle(
			vertices[prevVertexIndex],
			vertices[nextVertexIndex],
			vertices[clampIndex(nextVertexIndex + 1, 0, currNumVertices - 1)]
		);
		if (isClockWise(vertices[prevVertexIndex],
			vertices[nextVertexIndex],
			vertices[clampIndex(nextVertexIndex + 1, 0, currNumVertices - 1)])
			!= isPolygonClockWise)
			angles[nextVertexIndex] = 2.0f * pi - angles[nextVertexIndex];
		//bubble the used vertex and angle to the end of the arrays
		for (int j = minAngleIndex; j < currNumVertices - 1;j++) {
			float angle;
			glm::vec2 vertex;

			angle = angles[j];
			angles[j] = angles[j + 1];
			angles[j + 1] = angle;

			vertex = vertices[j];
			vertices[j] = vertices[j + 1];
			vertices[j + 1] = vertex;
		}
		currNumVertices--;

	}
	//enter vertices
	_verticesCount = (numVertices - 2) * 3;
	_vertices = new Vertex[_verticesCount];
	int j = 0;
	for (int i = 0;i < _verticesCount;i = i + 3) {
		_vertices[i] = { triangles[j].a.x,triangles[j].a.y	,1.0f,1.0f,1.0f };
		_vertices[i + 1] = { triangles[j].b.x,triangles[j].b.y		,1.0f,1.0f,1.0f };
		_vertices[i + 2] = { triangles[j].c.x,triangles[j].c.y	,1.0f,1.0f,1.0f };
		j++;
	}
}

bool Polygon::intersects(const Shape& other) {
	return other.isIntersecting(*this);
}

bool Polygon::isIntersecting(const Polygon& other) const
{
	//TODO - solve closest point
	glm::vec2 interPoint(0.0f);
	Line2D centerToCenter(_position, other.getPosition());
	//std::cout << "y=" << centerToCenter.slope << "x+" << centerToCenter.intercept << "  " << centerToCenter.leftLimit <<" , " << centerToCenter.rightLimit<< std::endl;
	glm::mat4 thisModel = getModelMatrix();
	for (int i = 0;i < _borderEdgesCount;i++) {
		glm::vec4 p1(_borders[i][0].x,_borders[i][0].y, 1.0f, 1.0f);
		p1 = thisModel*p1;
		glm::vec4 p2(_borders[i][1].x,_borders[i][1].y, 1.0f, 1.0f);
		p2 = thisModel * p2;
		//std::cout << p1.x << "," << p1.y << "    " << p2.x << "," << p2.y << std::endl;
		Line2D borderline(glm::vec2(p1.x, p1.y), glm::vec2(p2.x, p2.y));
		//std::cout << "edge" << i << ": y=" << borderline.slope << "x+" << borderline.intercept << "  "<<borderline.leftLimit<<" , "<<borderline.rightLimit<< std::endl;
		Line2D::LineIntersection closestPointToOther = centerToCenter.isIntersecting(borderline);
		if (closestPointToOther.isIntersecting)
		{
			interPoint = closestPointToOther.intersectionPoint;
			//std::cout << interPoint.x << "," << interPoint.y << std::endl;
		}
	}
	//std::cout << closestPointToOther.intersectionPoint.x << "," << closestPointToOther.intersectionPoint.y << std::endl;
	int otherBorderEdges = other.getNumEdges();
	glm::mat2* otherBorders = other.getBorder();
	glm::mat4 otherModel = other.getModelMatrix();
	Line2D* vertical;
	if (_position.x>other._position.x)
		vertical = new Line2D(glm::vec2(-600.0f, interPoint.y), glm::vec2(centerToCenter.rightLimit, interPoint.y));
	else
		vertical = new Line2D(glm::vec2(centerToCenter.leftLimit, interPoint.y), glm::vec2(600.0f, interPoint.y));
	int count = 0;
	for (int i = 0;i < otherBorderEdges;i++) {
		glm::vec4 p1(otherBorders[i][0], 1.0f, 1.0f);
		p1 = otherModel * p1;
		glm::vec4 p2(otherBorders[i][1], 1.0f, 1.0f);
		p2 = otherModel * p2;
		Line2D::LineIntersection check = vertical->isIntersecting(Line2D(glm::vec2(p1.x, p1.y), glm::vec2(p2.x, p2.y)));
		if (check.isIntersecting) count++;
	}
	delete vertical;
	return count % 2 != 0;
}

bool Polygon::isIntersecting(const Circle& other) const
{
	return true;
}
