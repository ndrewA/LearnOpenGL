#include "Timer.h"

#include <iostream>

namespace utilities
{
	long long Timer::getDeltaTime()
	{
		currentTime = getCurrentTime();
		long long deltaTime = std::chrono::duration_cast<std::chrono::nanoseconds>(currentTime - lastTime).count();
		return (float)deltaTime/1000000000;
	}

	void Timer::resetTimer()
	{
		lastTime = currentTime;
	}
}
