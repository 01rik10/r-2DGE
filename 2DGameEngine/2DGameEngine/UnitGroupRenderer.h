#pragma once
#include "Shape.h"
#include "GLSLProgram.h"
#include <vector>
#include <glm/gtc/type_ptr.hpp>
class UnitGroupRenderer
{
public:
	struct Vertex {
		Shape::Vertex v;
		int objID;
	};
	UnitGroupRenderer();
	void init(const std::vector<Shape*>& shapes, GLSLProgram* shader);
	void validate();
	void beforeDraw(const glm::mat4& view, const glm::mat4& projection);
	void loadUniforms();
	void draw();
private:
	//opengl objects
	unsigned int _vaoID;
	unsigned int _vboID;
	unsigned int _uboID;
	//unit holders
	std::vector<Shape*> _shapes;
	int _lastKnownUnitsSize;
	//shader program
	GLSLProgram* _shader;
	//checks if needs update to buffer after validation
	bool _needsUpdate;
	int _verticesCount;
	void bufferData();
};

