#pragma once

#include <chrono>

namespace System {

class MouseButtonState {
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
    MouseButtonState(float holdThreshold = 0.2f) : currentState(RELEASED), isCurrentlyPressed(false), holdThresholdSeconds(holdThreshold) {}

    void update(bool isPressed);
    State getState() const;
    bool isReleased() const;
    bool isPressed() const;
    bool isHolding() const;
    bool isJustReleased() const;
    float getHoldDuration() const;
};

} // namespace System
