#pragma once

#include <chrono>

namespace utilities
{
	class Timer
	{
	private:
		using time = std::chrono::steady_clock::time_point;

	public:
		Timer() {}
		float getDeltaTime();
		void resetTimer();

	private:
		time currentTime = getCurrentTime();
		time lastTime = getCurrentTime();

	private:
		time getCurrentTime() { return std::chrono::high_resolution_clock::now(); }
	};
}

