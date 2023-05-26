#include "Shape.h"

void Shape::setPosition(glm::vec2 position)
{
	_position = position;
	_translation = glm::translate(glm::mat4(1.0), glm::vec3(position, 0.0f));
}

void Shape::setRotation(float rotation)
{
	_rotationAngle = rotation;
	_rotation = glm::rotate(glm::mat4(1.0), rotation, glm::vec3(0.0, 0.0, -1.0));
}

glm::mat4 Shape::getModelMatrix() const
{
	return _translation * _rotation * _scale;
}
