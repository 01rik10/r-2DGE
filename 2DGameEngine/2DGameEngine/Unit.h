#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include "Time.h"
#include "Dynamics2D.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include "Tools.h"
#include "Shape.h"
#include <cmath>

//square sprites ,implement other inherited sprites later ( triangles,circles , other shapes..?)
class Unit
{
public:
	Unit();
	~Unit();

	//on each frame - if overriden - call this method after override function
	virtual void update(){
	}

	//getters
	virtual Shape* getShape() const { return shape; }
	virtual glm::vec2 getPosition() const{ return dynamics.position; }
	virtual glm::vec2 getVelocity() const { return dynamics.velocity; }
	virtual glm::vec2 getAcceleration() const { return dynamics.acceleration; }
	virtual float getRotate() const { return dynamics.rotation;}
protected:
	Shape* shape;
	Dynamics2D dynamics;
};

