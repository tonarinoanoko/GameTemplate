#include "System/Input/InputManager.h"

namespace Input {

InputManager::InputManager() {
    for (int key : watchedKeys) {
        keyStates.emplace(key, InputStateBase());
    }
}

InputManager& InputManager::getInstance() {
    static InputManager _instance;
    return _instance;
}

void InputManager::addWatchKey(int key) {
    if (keyStates.find(key) == keyStates.end()) {
        watchedKeys.push_back(key);
        keyStates.emplace(key, InputStateBase());
    }
}

void InputManager::update() {
    for (int key : watchedKeys) {
        keyStates[key].update(CheckHitKey(key) == 1);
    }
}

const InputStateBase& InputManager::getState(int key) const
{
    auto it = keyStates.find(key);
    if (it != keyStates.end()) {
        return it->second;
    }
    static const InputStateBase defaultState;
    return defaultState;
}

bool InputManager::isKeyPressed(int key) const
{
    return getState(key).isPressed();
}

bool InputManager::isKeyHolding(int key) const
{
    return getState(key).isHolding();
}

bool InputManager::isKeyJustReleased(int key) const
{
    return getState(key).isJustReleased();
}

bool InputManager::isKeyReleased(int key) const
{
    return getState(key).isReleased();
}

float InputManager::getKeyHoldDuration(int key) const
{
    return getState(key).getHoldDuration();
}

} // namespace Input
