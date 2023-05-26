#include "BatchRenderer.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
BatchRenderer::BatchRenderer() :_vboID(), _units(),_vertices(), _vertexCount(0)
{
}


void BatchRenderer::linkUnits(std::vector<Unit*>* units)
{
	_units = units;
}

void BatchRenderer::linkProgram(GLSLProgram* program)
{
	_program = program;
}

void BatchRenderer::beforeDraw(const glm::mat4& view, const glm::mat4& projection)
{
	//TODO- sort algorithm
	// set VP matrices
	//link id to a buffer object
	_view = view;
	_projection = projection;
	std::vector<glm::mat4> model;
	translations.clear();
	scales.clear();
	rotations.clear();
	if (_vboID == 0) {
		glGenBuffers(1, &_vboID);
	}
	int unitID = 0;
	for (Unit* u: *_units) {		
		//model = u->getModelMatrices();
		//u->prepDraw();
		translations.push_back(model.at(0));
		rotations.push_back(model.at(1));
		scales.push_back(model.at(2));
		//_vertexCount += u->getVerticesSize();
		//std::vector < Unit::Vertex > * verts = u->getVertices();
		//for (const Unit::Vertex& vert : *verts) {
		//	_vertices.push_back({ vert,unitID });
		//}
		unitID++;

	}
	int size = _units->size();
	_program->use();
	GLuint projectionID = _program->getUniformLocation("projection");
	GLuint viewID = _program->getUniformLocation("view");
	GLuint scaleID = _program->getUniformLocation("scale");
	GLuint rotationID = _program->getUniformLocation("rotation");
	GLuint translationID = _program->getUniformLocation("translation");
	glUniformMatrix4fv(projectionID, 1, false, glm::value_ptr(projection));
	glUniformMatrix4fv(viewID, 1, false, glm::value_ptr(view));
	glUniformMatrix4fv(translationID, size, false, glm::value_ptr(translations[0]));
	glUniformMatrix4fv(rotationID, size, false, glm::value_ptr(rotations[0]));
	glUniformMatrix4fv(scaleID, size, false, glm::value_ptr(scales[0]));
	//bind buffer - GL_ARRAY_BUFFER for simple vertices buffer
	glBindBuffer(GL_ARRAY_BUFFER, _vboID);
}

void BatchRenderer::drawBatch() {
	//load data to the binded buffer : (buffer type, size of data in bytes, pointer to the start of the data, draw type)
	glBufferData(GL_ARRAY_BUFFER, sizeof(S)*_vertices.size(), _vertices.data(), GL_DYNAMIC_DRAW);
	//sending only position(no shading features) so 0
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	//specify the draw funcionality :(start data,dimension(x,y),gl_type of data, normalize? false,stride?,pointer?)
	glVertexAttribPointer(0, 2, GL_FLOAT, false, sizeof(S), 0);
	glVertexAttribPointer(1, 3, GL_FLOAT,false, sizeof(S), reinterpret_cast<void*>(sizeof(GLfloat)*2));
	glVertexAttribIPointer(2, 1, GL_INT, sizeof(S), reinterpret_cast<void*>(sizeof(GLfloat) * 5));
	//actual draw (GL_MODE , start drawing from , num of vertices to draw(6 : 2 triangles))
	glDrawArrays(GL_TRIANGLES, 0, _vertexCount);
}
void BatchRenderer::afterDraw()
{
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	//unbind buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	_vertices.clear();
	_program->unuse();
	_vertexCount = 0;
}
