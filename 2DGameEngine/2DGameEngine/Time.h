#pragma once
#include <SDL/SDL_timer.h>
class Time
{
public:
	static void limitFps(int maxFps);
	static void frameStart();
	static void frameEnd();
	static float getDeltaTime();
private:
	static int _maxFps;
	static float _wantedFrameTime;
	//actual frame time
	static float _dt;
	static float _actualFps;
	//fps calculation
	static Uint64 _begin;
};

