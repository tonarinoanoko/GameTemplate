#pragma once

#include "InputStateBase.h"

namespace System {

class MouseInputState {
private:
    InputStateBase<int> leftButtonState;
    InputStateBase<int> rightButtonState;
    InputStateBase<int> middleButtonState;
    int x;
    int y;
    int deltaX;
    int deltaY;
    int wheelDelta;

public:
    MouseInputState(float holdThreshold = 0.2f) :
        leftButtonState(holdThreshold),
        rightButtonState(holdThreshold),
        middleButtonState(holdThreshold),
        x(0), y(0), deltaX(0), deltaY(0), wheelDelta(0)
    {}

    void update(int currentX, int currentY, int currentWheelDelta, bool leftButton, bool rightButton, bool middleButton);

    // 左ボタン関連
    typename InputStateBase<int>::State getLeftButtonState() const { return leftButtonState.getState(); }
    bool isLeftButtonPressed() const { return leftButtonState.isPressed(); }
    bool isLeftButtonHolding() const { return leftButtonState.isHolding(); }
    bool isLeftButtonJustReleased() const { return leftButtonState.isJustReleased(); }
    bool isLeftButtonReleased() const { return leftButtonState.isReleased(); }
    float getLeftButtonHoldDuration() const { return leftButtonState.getHoldDuration(); }

    // 右ボタン関連
    typename InputStateBase<int>::State getRightButtonState() const { return rightButtonState.getState(); }
    bool isRightButtonPressed() const { return rightButtonState.isPressed(); }
    bool isRightButtonHolding() const { return rightButtonState.isHolding(); }
    bool isRightButtonJustReleased() const { return rightButtonState.isJustReleased(); }
    bool isRightButtonReleased() const { return rightButtonState.isReleased(); }
    float getRightButtonHoldDuration() const { return rightButtonState.getHoldDuration(); }

    // 中ボタン関連
    typename InputStateBase<int>::State getMiddleButtonState() const { return middleButtonState.getState(); }
    bool isMiddleButtonPressed() const { return middleButtonState.isPressed(); }
    bool isMiddleButtonHolding() const { return middleButtonState.isHolding(); }
    bool isMiddleButtonJustReleased() const { return middleButtonState.isJustReleased(); }
    bool isMiddleButtonReleased() const { return middleButtonState.isReleased(); }
    float getMiddleButtonHoldDuration() const { return middleButtonState.getHoldDuration(); }

    // マウス座標
    int getX() const { return x; }
    int getY() const { return y; }
    int getDeltaX() const { return deltaX; }
    int getDeltaY() const { return deltaY; }
    int getWheelDelta() const { return wheelDelta; }
};

} // namespace System
