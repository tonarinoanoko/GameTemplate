#pragma once

#include <map>
#include <vector>
#include <DxLib.h>
#include "System/Input/InputStateBase.h"

namespace Input {

class InputManager {
public:
    // 静的インスタンスを取得するメソッド
    static InputManager& getInstance();

    void addWatchKey(int key);
    void update();

    const InputStateBase& getState(int key) const;
    bool isKeyPressed(int key) const;
    bool isKeyHolding(int key) const;
    bool isKeyJustReleased(int key) const;
    bool isKeyReleased(int key) const;
    float getKeyHoldDuration(int key) const;

private:
    InputManager();
    ~InputManager() = default;
    InputManager(const InputManager&) = delete;
    InputManager& operator=(const InputManager&) = delete;
    static InputManager _instance;

private:
    std::map<int, InputStateBase> keyStates;
    std::vector<int> watchedKeys = {
        KEY_INPUT_UP,
        KEY_INPUT_DOWN,
        KEY_INPUT_LEFT,
        KEY_INPUT_RIGHT,
        KEY_INPUT_SPACE,
        KEY_INPUT_Z
    };

};

} // namespace Input
