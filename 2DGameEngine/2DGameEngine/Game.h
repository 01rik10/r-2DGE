#pragma once
#include "Window.h"
#include <iostream>
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include "PongPlayer.h"
#include "InputManager.h"
#include "GLSLProgram.h"
#include "Camera2D.h"
#include "Ball.h"
#include "Time.h"
#include "Spaceship.h"
#include "RectengleUnit.h"
#include "Asteroid.h"
#include "Bullet.h"
#include "UnitGroupRenderer.h"
#include "Shape.h"
#include "IsoTriangle.h"
#include "Circle.h"
#include "Rectengle.h"
#include "Polygon.h"
#include "CollisionSolver.h"

using namespace std;
class Game
{
public:
	enum GameMode{PLAY , EXIT};
	Game();
	void run();
private:
	void initSystems();
	void gameLoop();
	void processUserEvent();
	void drawGame();
	void checkBallCollision(PongPlayer*);
	void shoot();
	Window _window;
	int _screenHeight;
	int _screenWidth;
	GameMode _gameMode;
	InputManager _inputManager;
	GLSLProgram* _gl;
	Camera2D _camera;
	std::vector<Unit*>* _units1;
	std::vector<Unit*>* _units2;
	std::vector<Asteroid*>* asteroids;
	std::vector<Shape*> shapes;
	Spaceship* _player;
	RectengleUnit* _rec;
	UnitGroupRenderer playerAndBullets;
};

