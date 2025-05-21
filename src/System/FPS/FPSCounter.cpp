#include "FPSCounter.h"
#include <sstream>
#include <iomanip>

FPSCounter::FPSCounter(float interval) : updateInterval(interval), elapsedTime(0.0f), frameCount(0), currentFPS(0.0f) {
    lastTime = Clock::now();
}

void FPSCounter::update() {
    TimePoint currentTime = Clock::now();
    Duration frameTime = currentTime - lastTime;
    lastTime = currentTime;

    elapsedTime += std::chrono::duration<float>(frameTime).count();
    frameCount++;

    if (elapsedTime >= updateInterval) {
        currentFPS = static_cast<float>(frameCount) / elapsedTime;
        frameCount = 0;
        elapsedTime -= updateInterval;
    }
}

std::string FPSCounter::getFormattedFPS() const {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(2) << currentFPS;
    return ss.str();
}
