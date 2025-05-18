#pragma once

#include "System/Input/MouseInputState.h"
#include <DxLib.h>

namespace Input {

class MouseInputManager {
private:
    MouseInputState state;

    // コンストラクタをprivateにする
    MouseInputManager();
    ~MouseInputManager() = default;
    MouseInputManager(const MouseInputManager&) = delete;
    MouseInputManager& operator=(const MouseInputManager&) = delete;

public:
    static MouseInputManager& getInstance();

    void update();

    const MouseInputState& getState() const { return state; }

    // 左ボタン関連
    bool isLeftButtonPressed() const;
    bool isLeftButtonHolding() const;
    bool isLeftButtonJustReleased() const;
    bool isLeftButtonReleased() const;
    float getLeftButtonHoldDuration() const;

    // 右ボタン関連
    bool isRightButtonPressed() const;
    bool isRightButtonHolding() const;
    bool isRightButtonJustReleased() const;
    bool isRightButtonReleased() const;
    float getRightButtonHoldDuration() const;

    // 中ボタン関連
    bool isMiddleButtonPressed() const;
    bool isMiddleButtonHolding() const;
    bool isMiddleButtonJustReleased() const;
    bool isMiddleButtonReleased() const;
    float getMiddleButtonHoldDuration() const;

    // マウス座標関連
    int getX() const;
    int getY() const;
    int getDeltaX() const;
    int getDeltaY() const;
    int getWheelDelta() const;
};

} // namespace Input
