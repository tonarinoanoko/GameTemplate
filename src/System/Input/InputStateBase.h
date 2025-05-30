#pragma once

#include <chrono>

namespace Input {

class InputStateBase {
public:
    enum eState {
        Released,
        Pressed,
        Holding,
        JustReleased
    };

public:
    InputStateBase(float holdThreshold = 0.2f) : currentState(Released), isCurrentlyPressed(false), holdThresholdSeconds(holdThreshold) {}

    void update(bool isInputActive) {
        auto now = std::chrono::steady_clock::now();

        if (isInputActive) {
            if (!isCurrentlyPressed) {
                currentState = eState::Pressed;
                pressedStartTime = now;
            } else {
                auto duration = std::chrono::duration_cast<std::chrono::duration<float>>(now - pressedStartTime);
                if (duration.count() >= holdThresholdSeconds) {
                    currentState = eState::Holding;
                } else {
                    currentState = eState::Pressed;
                }
            }
        } else {
            if (isCurrentlyPressed) {
                currentState = eState::JustReleased;
            } else {
                currentState = eState::Released;
            }
        }
        isCurrentlyPressed = isInputActive;
    }

    eState getState() const {
        return currentState;
    }

    bool isReleased() const {
        return currentState == eState::Released;
    }

    bool isPressed() const {
        return currentState == eState::Pressed;
    }

    bool isHolding() const {
        return currentState == eState::Holding;
    }

    bool isJustReleased() const {
        return currentState == eState::JustReleased;
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

private:
    eState currentState;
    bool isCurrentlyPressed;
    std::chrono::time_point<std::chrono::steady_clock> pressedStartTime;
    float holdThresholdSeconds;
};

} // namespace Input