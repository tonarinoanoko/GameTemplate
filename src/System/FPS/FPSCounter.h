#pragma once

#include <chrono>
#include <string>

namespace System {
namespace Utility {

class FPSCounter {
private:
    using Clock = std::chrono::high_resolution_clock;
    using TimePoint = Clock::time_point;
    using Duration = Clock::duration;
    using Milliseconds = std::chrono::duration<float, std::milli>;

    TimePoint lastTime;
    int frameCount;
    float currentFPS;
    float updateInterval; // FPS を更新する間隔 (秒)
    float elapsedTime;

public:
    FPSCounter(float interval = 0.5f); // 更新間隔を引数で指定可能
    ~FPSCounter() = default;

    void update();
    float getFPS() const { return currentFPS; }
    std::string getFormattedFPS() const;
};

} // namespace Utility
} // namespace System
