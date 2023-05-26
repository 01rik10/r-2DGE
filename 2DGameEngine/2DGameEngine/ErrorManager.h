#pragma once
#include <iostream>
#include <string>
#include <SDL/SDL.h>
class ErrorManager
{
public:
	static void error(const std::string& error);
};

