#pragma once

#include <chrono>
#include <thread>

class FPSLimiter {
private:
    using Clock = std::chrono::high_resolution_clock;
    using TimePoint = Clock::time_point;
    using Duration = Clock::duration;
    using Microseconds = std::chrono::duration<long long, std::micro>;

    float targetFPS;
    Microseconds targetFrameTime;
    TimePoint frameStartTime;

public:
    FPSLimiter(float fps);
    ~FPSLimiter() = default;

    void setTargetFPS(float fps);
    float getTargetFPS() const { return targetFPS; }

    void beginFrame();
    void endFrame();
};
