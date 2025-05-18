#include "PauseScene.h"
#include "System/Input/InputManager.h"
#include "System/Scene/SceneManager.h"
#include <DxLib.h>

namespace Scene {

PauseScene::PauseScene() {}

void PauseScene::initialize() {
    // ポーズメニューの初期化
}

void PauseScene::update() {
    // ポーズメニューの操作
    if (System::InputManager::getInstance().isKeyPressed(KEY_INPUT_P)) {
        System::Scene::SceneManager::getInstance().resumeGame();
    }
}

void PauseScene::draw() {
    // ポーズメニューの描画
    DrawString(200, 200, "PAUSE", GetColor(255, 255, 255));
    DrawString(200, 220, "Press 'P' to Resume", GetColor(255, 255, 255));
}

void PauseScene::finalize() {
    // ポーズメニューの終了処理
}

} // namespace Scene
