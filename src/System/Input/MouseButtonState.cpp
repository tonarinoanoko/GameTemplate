#include "MouseButtonState.h"

namespace Input {

void MouseButtonState::update(bool isPressed) {
    auto now = std::chrono::steady_clock::now();

    if (isPressed) {
        if (!isCurrentlyPressed) {
            currentState = PRESSED;
            pressedStartTime = now;
        } else {
            auto duration = std::chrono::duration_cast<std::chrono::duration<float>>(now - pressedStartTime);
            if (duration.count() >= holdThresholdSeconds) {
                currentState = HOLDING;
            } else {
                currentState = PRESSED;
            }
        }
    } else {
        if (isCurrentlyPressed) {
            currentState = JUST_RELEASED;
        } else {
            currentState = RELEASED;
        }
    }
    isCurrentlyPressed = isPressed;
}

MouseButtonState::State MouseButtonState::getState() const {
    return currentState;
}

bool MouseButtonState::isReleased() const {
    return currentState == RELEASED;
}

bool MouseButtonState::isPressed() const {
    return currentState == PRESSED;
}

bool MouseButtonState::isHolding() const {
    return currentState == HOLDING;
}

bool MouseButtonState::isJustReleased() const {
    return currentState == JUST_RELEASED;
}

float MouseButtonState::getHoldDuration() const {
    if (isCurrentlyPressed) {
        auto now = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::duration<float>>(now - pressedStartTime);
        return duration.count();
    } else {
        return 0.0f;
    }
}

} // namespace Input
