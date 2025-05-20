#include "FPSLimiter.h"
#include <iostream> // デバッグ用 (必要に応じて削除)

namespace System {
namespace Utility {

FPSLimiter::FPSLimiter(float fps) : targetFPS(fps) {
    if (fps > 0) {
        targetFrameTime = Microseconds(static_cast<long long>(1000000.0f / fps));
    } else {
        targetFrameTime = Microseconds(0); // FPS 制限なし
    }
}

void FPSLimiter::setTargetFPS(float fps) {
    targetFPS = fps;
    if (fps > 0) {
        targetFrameTime = Microseconds(static_cast<long long>(1000000.0f / fps));
    } else {
        targetFrameTime = Microseconds(0);
    }
}

void FPSLimiter::beginFrame() {
    frameStartTime = Clock::now();
}

void FPSLimiter::endFrame() {
    if (targetFPS > 0) {
        TimePoint frameEndTime = Clock::now();
        Microseconds frameDuration = std::chrono::duration_cast<Microseconds>(frameEndTime - frameStartTime);
        Microseconds sleepTime = targetFrameTime - frameDuration;

        if (sleepTime.count() > 0) {
            std::this_thread::sleep_for(sleepTime);
        }
        // 必要であれば、実際の FPS を計測してログ出力するなど
        // TimePoint actualEndTime = Clock::now();
        // Microseconds actualFrameDuration = std::chrono::duration_cast<Microseconds>(actualEndTime - frameStartTime);
        // float actualFPS = 1000000.0f / actualFrameDuration.count();
        // std::cout << "Target: " << targetFPS << " Actual: " << actualFPS << std::endl;
    }
}

} // namespace Utility
} // namespace System
