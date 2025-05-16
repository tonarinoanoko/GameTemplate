#include "System/Input/MouseInputManager.h"
#include <DxLib.h>

namespace System {

MouseInputManager::MouseInputManager() {}

MouseInputManager& MouseInputManager::getInstance() {
    static MouseInputManager instance;
    return instance;
}

void MouseInputManager::update() {
    int x, y, wheelDelta, buttonState;
    buttonState = GetMouseInput();
    GetMousePoint(&x, &y);
    wheelDelta = GetMouseWheelRotVol();
    state.update(x, y, wheelDelta, buttonState & 0x01, buttonState & 0x02, buttonState & 0x04);
}

bool MouseInputManager::isLeftButtonPressed() const { return state.isLeftButtonPressed(); }
bool MouseInputManager::isLeftButtonHolding() const { return state.isLeftButtonHolding(); }
bool MouseInputManager::isLeftButtonJustReleased() const { return state.isLeftButtonJustReleased(); }
bool MouseInputManager::isLeftButtonReleased() const { return state.isLeftButtonReleased(); }
float MouseInputManager::getLeftButtonHoldDuration() const { return state.getLeftButtonHoldDuration(); }

bool MouseInputManager::isRightButtonPressed() const { return state.isRightButtonPressed(); }
bool MouseInputManager::isRightButtonHolding() const { return state.isRightButtonHolding(); }
bool MouseInputManager::isRightButtonJustReleased() const { return state.isRightButtonJustReleased(); }
bool MouseInputManager::isRightButtonReleased() const { return state.isRightButtonReleased(); }
float MouseInputManager::getRightButtonHoldDuration() const { return state.getRightButtonHoldDuration(); }

bool MouseInputManager::isMiddleButtonPressed() const { return state.isMiddleButtonPressed(); }
bool MouseInputManager::isMiddleButtonHolding() const { return state.isMiddleButtonHolding(); }
bool MouseInputManager::isMiddleButtonJustReleased() const { return state.isMiddleButtonJustReleased(); }
bool MouseInputManager::isMiddleButtonReleased() const { return state.isMiddleButtonReleased(); }
float MouseInputManager::getMiddleButtonHoldDuration() const { return state.getMiddleButtonHoldDuration(); }

int MouseInputManager::getX() const { return state.getX(); }
int MouseInputManager::getY() const { return state.getY(); }
int MouseInputManager::getDeltaX() const { return state.getDeltaX(); }
int MouseInputManager::getDeltaY() const { return state.getDeltaY(); }
int MouseInputManager::getWheelDelta() const { return state.getWheelDelta(); }

} // namespace System
