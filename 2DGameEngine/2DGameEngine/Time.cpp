#include "Time.h"
#include <iostream>
int Time::_maxFps=60;
float Time::_wantedFrameTime=1000.0f/60.0f;
//actual frame time
float Time::_dt=1000.0f/60.0f;
float Time::_actualFps=60.0f;
//fps calculation
Uint64 Time::_begin=SDL_GetTicks();
void Time::limitFps(int maxFps)
{
	Time::_maxFps,Time::_actualFps = maxFps;
	Time::_wantedFrameTime =  1000.0f/maxFps;
	std::cout << Time::_wantedFrameTime << std::endl;
}

void Time::frameStart()
{
	_begin = SDL_GetTicks();
}

void Time::frameEnd()
{
	//fps calculation
	Uint64 dt = SDL_GetTicks() - _begin;
	//fps limit
	if (Time::_wantedFrameTime > dt) {
		SDL_Delay(Time::_wantedFrameTime - dt);
	}
	Time::_dt = (SDL_GetTicks() - _begin)/1000.0f;
	Time::_actualFps =  1.0f/_dt;
	//std::cout << _actualFps << std::endl;
	//std::cout << _dt << std::endl;
}

float Time::getDeltaTime()
{
	return Time::_dt;
}
