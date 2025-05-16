#pragma once

#include <map>
#include <vector>
#include <DxLib.h>
#include "System/Input/InputStateBase.h"

namespace System {

class InputManager {
private:
    std::map<int, InputStateBase<int>> keyStates;
    std::vector<int> watchedKeys;

    // コンストラクタをprivateにする
    InputManager();
    // デストラクタ (必要に応じて)
    ~InputManager() = default;
    // コピーコンストラクタとコピー代入演算子を削除
    InputManager(const InputManager&) = delete;
    InputManager& operator=(const InputManager&) = delete;

public:
    // 静的インスタンスを取得するメソッド
    static InputManager& getInstance();

    void addWatchKey(int key);
    void update();

    const InputStateBase<int>& getState(int key) const;
    bool isKeyPressed(int key) const;
    bool isKeyHolding(int key) const;
    bool isKeyJustReleased(int key) const;
    bool isKeyReleased(int key) const;
    float getKeyHoldDuration(int key) const;
};

} // namespace System
