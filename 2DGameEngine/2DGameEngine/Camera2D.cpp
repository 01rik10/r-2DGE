#include "Camera2D.h"

Camera2D::Camera2D(float screenWidth, float screenHeight)
{
	_screenHeight = screenHeight;
	_screenWidth = screenWidth;
	glm::vec3 vec3(1.0f / (screenWidth/2.0f), 1 / (screenHeight/2.0f), 1.0f);
	worldToCCP = glm::mat4(1.0f);
	worldToCCP = glm::scale(worldToCCP, vec3);
}

glm::vec4 Camera2D::convertWorldToCCP(glm::vec4 vec)
{
	return worldToCCP*vec;
}

glm::mat4 Camera2D::getScale()
{
	return worldToCCP;
}
