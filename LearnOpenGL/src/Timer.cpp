#include "Timer.h"

#include <iostream>

namespace utilities
{
	float Timer::getDeltaTime()
	{
		auto deltaTime = std::chrono::duration_cast<std::chrono::nanoseconds>(currentTime - lastTime).count();
		lastTime = currentTime;
		currentTime = getCurrentTime();
		return (float)deltaTime/1000000000;
	}

	void Timer::resetTimer()
	{
		lastTime = currentTime;
	}
}
