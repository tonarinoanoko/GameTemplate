#include "MouseInputState.h"


namespace Input {

void MouseInputState::update(int currentX, int currentY, int currentWheelDelta, bool leftButton, bool rightButton, bool middleButton) {
    deltaX = currentX - x;
    deltaY = currentY - y;
    x = currentX;
    y = currentY;
    wheelDelta = currentWheelDelta;

    leftButtonState.update(leftButton);
    rightButtonState.update(rightButton);
    middleButtonState.update(middleButton);
}

} // namespace Input
