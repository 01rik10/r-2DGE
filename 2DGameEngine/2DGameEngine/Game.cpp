#include "Game.h"
Game::Game() :_window(), _screenHeight(1080 / 2), _screenWidth(1920 / 2), _gameMode(PLAY), _inputManager(),
_gl(new GLSLProgram()), _camera(_screenWidth, _screenHeight),
_units1(new std::vector<Unit*>), _units2(new std::vector<Unit*>),asteroids(new std::vector<Asteroid*>),shapes(),
_player(new Spaceship()), _rec(new RectengleUnit())
 {}
void Game::run()
{
	initSystems();
	//start game loop
	gameLoop();
}

void Game::initSystems()
{
	_window.open(_screenWidth, _screenHeight);
	_inputManager.start();
	_gl->compileShaders("shaders\\SimpleShader.vert.txt",
		"shaders\\SimpleShader.frag.txt");
	_gl->linkShaders();
	//_br1.linkUnits(_units1);
	//_br2.linkUnits(_units2);
	//_br1.linkProgram(_gl);
	//_br2.linkProgram(_gl);
	Time::limitFps(60);


	_player = new Spaceship();
	shapes.push_back(_player->getShape());
	//setup lvl1
	Asteroid* a = new Asteroid(glm::vec2(-200,0),glm::vec2(2,0));
	Asteroid* b = new Asteroid(glm::vec2(-480, 200), glm::vec2(2, 0));
	Asteroid* c = new Asteroid(glm::vec2(-480, -200), glm::vec2(2, 0));
	Asteroid* d = new Asteroid(glm::vec2(480, 0), glm::vec2(-2, 0));
	Asteroid* e = new Asteroid(glm::vec2(480, 200), glm::vec2(-2, 0));
	Asteroid* f = new Asteroid(glm::vec2(480, -200), glm::vec2(-2, 0));
	asteroids->push_back(a);
	asteroids->push_back(b);
	asteroids->push_back(c);
	asteroids->push_back(d);
	asteroids->push_back(e);
	asteroids->push_back(f);
	
	shapes.push_back(a->getShape());
	shapes.push_back(b->getShape());
	shapes.push_back(c->getShape());
	shapes.push_back(d->getShape());
	shapes.push_back(e->getShape());
	shapes.push_back(f->getShape());
	

	playerAndBullets.init(shapes,_gl);
	//for (int i = 0;i < 20;i++) {
	//	_units2->push_back(new Asteroid());
	//}
	std::cout << GL_MAX_VERTEX_UNIFORM_COMPONENTS << std::endl;
	
}

void Game::checkBallCollision(PongPlayer* player)
{
	//glm::vec2 centeredPlayerPos;
	//centeredPlayerPos.x = player->getPosition().x + player->getWidth() / 2.0f;
	//centeredPlayerPos.y = player->getPosition().y + player->getHeight() / 2.0f;
	//glm::vec2 ballToPlayerCenters; // centeredPlayerPos - ball->getPosition();
	//ballToPlayerCenters.x = std::abs(ballToPlayerCenters.x);
	//ballToPlayerCenters.y = std::abs(ballToPlayerCenters.y);
	//glm::vec2 RectDelimiters;
	//RectDelimiters.x = std::min(player->getWidth() / 2.0f,(ballToPlayerCenters.x));
	//RectDelimiters.y = std::min(player->getHeight() / 2.0f,(ballToPlayerCenters.y));
	//glm::vec2 sub = ballToPlayerCenters - RectDelimiters;
	//if (glm::length(sub) <= ball->getRadius()) ball->collide();
}
void Game::shoot()
{
	//_units1->push_back(new Bullet(_player->getRotate(), _player->getPosition()));
}
void Game::gameLoop()
{
	while (_gameMode == PLAY) {
		Time::frameStart();
		processUserEvent();
		//naive collision
		for (Unit* u : *asteroids) {
			if (u->getShape()->intersects(*(_player->getShape()))) std::cout << "Intersecting" << std::endl;
		}
		//player+bullets update
		_player->update();
		for (Unit* u : *asteroids) {
			u->update();
		}
		_window.beforeDraw();
		drawGame();
		_window.afterDraw();
		Time::frameEnd();
	}
}

void Game::processUserEvent()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			_gameMode = EXIT;
			break;
		case SDL_KEYDOWN:
			_inputManager.keyPressed(event.key.keysym.scancode);
			//std::cout << event.key.keysym.scancode << std::endl;
			break;
		case SDL_KEYUP:
			_inputManager.keyReleased(event.key.keysym.scancode);
		}
	}
	if (_inputManager.isKeyPressed(4)) _player->rotateLeft();
	if (_inputManager.isKeyPressed(7)) _player->rotateRight();
	if (_inputManager.isKeyPressed(26)) _player->accelerate();
	else _player->stopAccelerate();
	if (_inputManager.isKeyPressed(44)) {
		shoot();
		_inputManager.keyReleased(44);
	}
	//if (_inputManager.isKeyPressed(79)) _player2->moveRight();
	//if (_inputManager.isKeyPressed(80)) _player2->moveLeft();
}

void Game::drawGame()
{
	//player and bullets draw
	//_br1.beforeDraw(_camera.getScale(),glm::mat4(1.0));
	//_br1.drawBatch();
	//_br1.afterDraw();
	//asteroids draw
	//_br2.beforeDraw(_camera.getScale(), glm::mat4(1.0));
	//_br2.drawBatch();
	//_br2.afterDraw();
	playerAndBullets.beforeDraw(_camera.getScale(),glm::mat4(1.0f));
}

