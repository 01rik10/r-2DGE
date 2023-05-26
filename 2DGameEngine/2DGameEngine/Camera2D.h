#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <iostream>
class Camera2D
{
public:
	//static for now
	Camera2D(float screenWidth, float screenHeight);
	glm::vec4 convertWorldToCCP(glm::vec4 vec);
	glm::mat4 getScale();
private:
	glm::mat4 worldToCCP;
	float _screenWidth;
	float _screenHeight;
};

