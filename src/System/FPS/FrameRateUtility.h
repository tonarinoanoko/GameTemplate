#pragma once

namespace System {
namespace Utility {

class FrameRateUtility {
private:
    float targetFPS;
    float deltaTime; // 1フレームあたりの目標時間 (秒)

public:
    FrameRateUtility(float fps);
    void setTargetFPS(float fps);
    float getDeltaTime() const { return deltaTime; }

    // 目標時間に基づいて、実際の経過時間から補正されたカウント数を取得する
    float getCompensatedCount(float elapsedTime, float baseSpeed);
    int getCompensatedIntegerCount(float elapsedTime, float baseSpeed);
};

} // namespace Utility
} // namespace System
