#pragma once

#include <chrono>

class Timer
{
public:
    using Clock = std::chrono::high_resolution_clock;
    using TimePoint = std::chrono::time_point<Clock>;
    using Duration = std::chrono::duration<float>;


    Timer()
        : startTime(Clock::now()) { }

    float mark()
    {
        TimePoint old = startTime;
        startTime = Clock::now();
        return Duration(startTime - old).count();
    }

    float getDeltaTime()
    {
        return Duration(Clock::now() - startTime).count();
    }

private:
    TimePoint startTime;
};