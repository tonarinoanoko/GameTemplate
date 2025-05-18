#include "System/Input/InputManager.h"

namespace Input {

InputManager::InputManager() {
    watchedKeys = { KEY_INPUT_UP, KEY_INPUT_DOWN, KEY_INPUT_LEFT, KEY_INPUT_RIGHT, KEY_INPUT_SPACE, KEY_INPUT_Z };
    for (int key : watchedKeys) {
        keyStates.emplace(key, InputStateBase<int>());
    }
}

InputManager& InputManager::getInstance() {
    static InputManager instance; // 静的ローカル変数はスレッドセーフに初期化される (C++11以降)
    return instance;
}

void InputManager::addWatchKey(int key) {
    if (keyStates.find(key) == keyStates.end()) {
        watchedKeys.push_back(key);
        keyStates.emplace(key, InputStateBase<int>());
    }
}

void InputManager::update() {
    for (int key : watchedKeys) {
        keyStates[key].update(CheckHitKey(key) == 1);
    }
}

const InputStateBase<int>& InputManager::getState(int key) const {
    auto it = keyStates.find(key);
    if (it != keyStates.end()) {
        return it->second;
    }
    static const InputStateBase<int> defaultState;
    return defaultState;
}

bool InputManager::isKeyPressed(int key) const {
    return getState(key).isPressed();
}

bool InputManager::isKeyHolding(int key) const {
    return getState(key).isHolding();
}

bool InputManager::isKeyJustReleased(int key) const {
    return getState(key).isJustReleased();
}

bool InputManager::isKeyReleased(int key) const {
    return getState(key).isReleased();
}

float InputManager::getKeyHoldDuration(int key) const {
    return getState(key).getHoldDuration();
}

} // namespace Input
