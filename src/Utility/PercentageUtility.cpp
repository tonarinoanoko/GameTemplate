#include "PercentageUtility.h"


namespace Utility {

float PercentageUtility::calculatePercentageNormalized(float value1, float value2) {
    if (value2 == 0.0f) {
        return 0.0f; // ゼロ除算を避ける
    }
    return value1 / value2;
}

float PercentageUtility::calculatePercentage(float value1, float value2) {
    return calculatePercentageNormalized(value1, value2) * 100.0f;
}

} // namespace Utility
