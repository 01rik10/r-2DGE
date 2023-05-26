#pragma once
#include <GL/glew.h>
#include <vector>
#include "Unit.h"
#include "GLSLProgram.h"
#include <glm/gtc/type_ptr.hpp>
/*BatchRenderer responsible for all the drawing*/
class BatchRenderer
{
public:
	BatchRenderer();
	void linkUnits(std::vector<Unit*>* units);
	void linkProgram(GLSLProgram* program);
	void beforeDraw(const glm::mat4& view, const glm::mat4& projection);
	void drawBatch();
	void afterDraw();
private:
	//vertex buffer object(VBO) id
	unsigned int _vboID;
	unsigned int _vaoID;
	bool flag = false;
	//sprite holder
	struct S {
		//Unit::Vertex v;
		int unitID;
	};
	std::vector<Unit*>* _units;
	std::vector<S> _vertices;
	GLSLProgram* _program;
	glm::mat4 _view;
	glm::mat4 _projection;
	std::vector<glm::mat4> translations;
	std::vector<glm::mat4> rotations;
	std::vector<glm::mat4> scales;
	int _vertexCount;
};

