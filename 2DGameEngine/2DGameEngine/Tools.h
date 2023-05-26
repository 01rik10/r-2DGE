#pragma once
#include <SDL/SDL.h>
#include <SDL/SDL_timer.h>
#include <cstdlib>
class Tools
{
public:
	static int random(int maxNum) {
		return (SDL_GetTicks()+rand()) % maxNum;
	}
};

