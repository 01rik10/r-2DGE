#include "Window.h"

Window::Window() :_errorManager(), _window(), _screenWidth(), _screenHeight()
{
}

void Window::open(int screenWidth,int screenHeight)
{
	_screenWidth = screenWidth;
	_screenHeight = screenHeight;
	//Initialize SDL
	SDL_Init(SDL_INIT_EVERYTHING);
	//Initialize window
	_window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _screenWidth, _screenHeight, SDL_WINDOW_OPENGL);
	if (_window == nullptr) {
		error("SDL window initialization error");
	}

	//Initialize opengl context
	SDL_GLContext gl_context = SDL_GL_CreateContext(_window);
	if (gl_context == nullptr) {
		error(SDL_GetError());
	}
	//Initialize glue
	GLenum e = glewInit();
	if (e) {
		error("Glew initialization error");
	}
	//set double buffer attribute , drawing one window while showing the other.
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
}

void Window::beforeDraw()
{
	//set depth - experiment later
	glClearDepth(1.0);
	//clear color and depth buffer - bitwise operation
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::afterDraw()
{
	//swap between 2 availble buffers
	SDL_GL_SwapWindow(_window);
}

void Window::error(const std::string& error)
{
	_errorManager.error(error);
	SDL_Quit();
}
