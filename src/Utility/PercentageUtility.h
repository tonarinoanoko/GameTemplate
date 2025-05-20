#pragma once

namespace Utility {

class PercentageUtility {
public:
    // value1 が value2 に対して何パーセントかを返す (0.0 ~ 100.0)
    static float calculatePercentage(float value1, float value2);

    // value1 が value2 に対して何パーセントかを 0.0 ~ 1.0 の範囲で返す
    static float calculatePercentageNormalized(float value1, float value2);
};

} // namespace Utility
