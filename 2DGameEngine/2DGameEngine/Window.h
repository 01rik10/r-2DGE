#pragma once
#include <SDL/SDL.h>
#include <GL/glew.h>
#include <iostream>
#include <string>
#include "ErrorManager.h"
/*Window class - using SDL and Glew*/
class Window
{
public:
	Window();
	void open(int screenWidth,int screenHeight);
	void beforeDraw();
	void afterDraw();
	void error(const std::string& error);
private:
	ErrorManager _errorManager;
	SDL_Window* _window;
	int _screenHeight;
	int _screenWidth;
};

