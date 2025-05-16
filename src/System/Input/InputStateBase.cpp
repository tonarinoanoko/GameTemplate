#include "InputStateBase.h"

namespace System {

template <typename InputType>
void InputStateBase<InputType>::update(bool isInputActive) {
    auto now = std::chrono::steady_clock::now();

    if (isInputActive) {
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
    isCurrentlyPressed = isInputActive;
}

template <typename InputType>
typename InputStateBase<InputType>::State InputStateBase<InputType>::getState() const {
    return currentState;
}

template <typename InputType>
bool InputStateBase<InputType>::isReleased() const {
    return currentState == RELEASED;
}

template <typename InputType>
bool InputStateBase<InputType>::isPressed() const {
    return currentState == PRESSED;
}

template <typename InputType>
bool InputStateBase<InputType>::isHolding() const {
    return currentState == HOLDING;
}

template <typename InputType>
bool InputStateBase<InputType>::isJustReleased() const {
    return currentState == JUST_RELEASED;
}

template <typename InputType>
float InputStateBase<InputType>::getHoldDuration() const {
    if (isCurrentlyPressed) {
        auto now = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::duration<float>>(now - pressedStartTime);
        return duration.count();
    } else {
        return 0.0f;
    }
}

} // namespace System
