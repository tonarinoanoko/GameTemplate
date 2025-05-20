#include "FrameRateUtility.h"
#include <cmath>

namespace System {
namespace Utility {

FrameRateUtility::FrameRateUtility(float fps) : targetFPS(fps) {
    if (fps > 0) {
        deltaTime = 1.0f / fps;
    } else {
        deltaTime = 0.0f;
    }
}

void FrameRateUtility::setTargetFPS(float fps) {
    targetFPS = fps;
    if (fps > 0) {
        deltaTime = 1.0f / fps;
    } else {
        deltaTime = 0.0f;
    }
}

float FrameRateUtility::getCompensatedCount(float elapsedTime, float baseSpeed) {
    if (deltaTime <= 0.0f) {
        return baseSpeed; // FPS 制限なしの場合はそのまま返す
    }
    return baseSpeed * (elapsedTime / deltaTime);
}

int FrameRateUtility::getCompensatedIntegerCount(float elapsedTime, float baseSpeed) {
    return static_cast<int>(std::round(getCompensatedCount(elapsedTime, baseSpeed)));
}

} // namespace Utility
} // namespace System
