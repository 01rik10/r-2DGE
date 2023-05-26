#include "UnitGroupRenderer.h"
#include <iostream>
UnitGroupRenderer::UnitGroupRenderer() :_vaoID(0), _vboID(0), _uboID(0), _shapes(),_lastKnownUnitsSize(0), _shader(), _needsUpdate(true), _verticesCount(0)
{
}

void UnitGroupRenderer::init(const std::vector<Shape*>& shapes, GLSLProgram* shader)
{
	glGenBuffers(1, &_uboID);
	glBindBuffer(GL_UNIFORM_BUFFER, _uboID);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	_shapes = shapes;
	_shader = shader;
	for (Shape* s : shapes) {
		_verticesCount += s->getVerticesCount();
	}
	Vertex* draw1 = new Vertex[_verticesCount];
	int i = 0;
	int objID = 0;
	for (Shape* s : shapes) {
		for (int j = 0;j < s->getVerticesCount();j++) {
			draw1[i] = Vertex{ s->getVertices()[j] , objID };
			i++;
		}
		objID++;
	}
	for (i = 0;i < _verticesCount;i++) {
	}
	//init vao
	glGenVertexArrays(1, &_vaoID);
	glBindVertexArray(_vaoID);
	//init vbo
	glGenBuffers(1, &_vboID);
	glBindBuffer(GL_ARRAY_BUFFER, _vboID);
	//buffer data - checks if needs change
	//bufferData();
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * _verticesCount , draw1 , GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(0, 2, GL_FLOAT, false, sizeof(Vertex), 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, false, sizeof(Vertex), reinterpret_cast<void*>(sizeof(GLfloat) * 2));
	glVertexAttribIPointer(2, 1, GL_INT, sizeof(Vertex), reinterpret_cast<void*>(sizeof(GLfloat) * 5));


	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//init vao
	glBindVertexArray(0);
	//_lastKnownUnitsSize = units->size();
	delete[]draw1;

}


void UnitGroupRenderer::validate()
{
	//std::vector<Unit*> sortme = *_units;
	//std::qsort(_units->data(), _units->size(), sizeof(Unit*)
	//	, [](const void* x, const void* y) {
	//		const Unit* arg1 = *(const Unit* const*)x;
	//		const Unit* arg2 = *(const Unit* const*)y;
	//		if (arg1->isExpired() == arg2->isExpired()) {
	//			return 0;
	//		}
	//		if (arg1->isExpired() && !arg2->isExpired()) {
	//			return 1;
	//		}
	//		else {
	//			return -1;
	//		}
	//	});
	//int i = _units->size()-1;
	//while (_units->at(i)->isExpired()) {
	//	delete _units->at(i);
	//	_units->pop_back();
	//	i--;
	//	_needsUpdate = true;
	//}
	//for (int i = 0;i < _units->size();i++) {
	//	if (_units->at(i)->isExpired()) {
	//		delete _units->at(i);
	//		_units->erase(_units->begin()+i);
	//		_needsUpdate = true;
	//		_lastKnownUnitsSize = _units->size();
	//	}
	//}
}

void UnitGroupRenderer::beforeDraw(const glm::mat4& view, const glm::mat4& projection)
{
	//if (_units->size() != _lastKnownUnitsSize) {
	//	_lastKnownUnitsSize = _units->size();
	//	_needsUpdate = true;
	//	std::cout << "here" << std::endl;
	//}
	validate();
	_shader->use();
	GLuint projectionID = _shader->getUniformLocation("projection");
	GLuint viewID = _shader->getUniformLocation("view");
	glUniformMatrix4fv(projectionID, 1, false, glm::value_ptr(projection));
	glUniformMatrix4fv(viewID, 1, false, glm::value_ptr(view));
	loadUniforms();
	glBindVertexArray(_vaoID);
	bufferData();
	glDrawArrays(GL_TRIANGLES,0,_verticesCount);
	glBindVertexArray(0);
	_shader->unuse();
}

void UnitGroupRenderer::loadUniforms()
{
	std::vector<glm::mat4> models;
	for (Shape* u : _shapes) {
		models.push_back(u->getModelMatrix());
	}
	glBindBuffer(GL_UNIFORM_BUFFER, _uboID);
	GLuint id = _shader->getUniformBlockIndex("Models");
	glBufferData(GL_UNIFORM_BUFFER, _shapes.size() * sizeof(glm::mat4), models.data(), GL_STATIC_DRAW);
	glBindBufferRange(GL_UNIFORM_BUFFER,id, _uboID, 0, sizeof(glm::mat4) * _shapes.size());
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void UnitGroupRenderer::bufferData()
{
	//if (_needsUpdate) {
	//	std::vector<Vertex> verticesToBuff;
	//	int objID = 0;
	//	for (Shape* s : _shapes) {
	//		for (const Shape::Vertex& v : *u->getVertices()) {
	//			verticesToBuff.push_back({ v,objID });
	//		}
	//		objID++;
	//	}
	//	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*verticesToBuff.size(), verticesToBuff.data(), GL_STATIC_DRAW);
	//	_verticesCount = verticesToBuff.size();
	//	std::cout << sizeof(Vertex) * verticesToBuff.size() << std::endl;
	//	_needsUpdate = false;
	//}
}


