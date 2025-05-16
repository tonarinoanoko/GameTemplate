#pragma once

#include <chrono>

namespace System {

template <typename InputType>
class InputStateBase {
public:
    enum State {
        RELEASED,
        PRESSED,
        HOLDING,
        JUST_RELEASED
    };

private:
    State currentState;
    bool isCurrentlyPressed;
    std::chrono::time_point<std::chrono::steady_clock> pressedStartTime;
    float holdThresholdSeconds;

public:
    InputStateBase(float holdThreshold = 0.2f) : currentState(RELEASED), isCurrentlyPressed(false), holdThresholdSeconds(holdThreshold) {}

    void update(bool isInputActive) {
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

    State getState() const {
        return currentState;
    }

    bool isReleased() const {
        return currentState == RELEASED;
    }

    bool isPressed() const {
        return currentState == PRESSED;
    }

    bool isHolding() const {
        return currentState == HOLDING;
    }

    bool isJustReleased() const {
        return currentState == JUST_RELEASED;
    }

    float getHoldDuration() const {
        if (isCurrentlyPressed) {
            auto now = std::chrono::steady_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::duration<float>>(now - pressedStartTime);
            return duration.count();
        } else {
            return 0.0f;
        }
    }
};

} // namespace System