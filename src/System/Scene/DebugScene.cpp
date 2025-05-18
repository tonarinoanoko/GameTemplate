#include "DebugScene.h"
#include <DxLib.h>
#include "System/Scene/SceneManager.h"
#include "System/Input/InputManager.h"
#include "Utility/ColorUtility.h" // ColorUtility のインクルード


namespace Scene {

DebugScene::DebugScene() {}

void DebugScene::initialize() {
    // デバッグ情報の初期化
}

void DebugScene::update() {
    if (System::InputManager::getInstance().isKeyPressed(KEY_INPUT_I)) {
        sceneInfoDebugger.setVisible(!sceneInfoDebugger.visible());
    }
}

void DebugScene::draw() {
    DrawString(10, 10, "Debug Mode", COLOR_WHITE);
    DrawString(10, 30, "Press 'I' to toggle Scene Info", COLOR_WHITE);

    const SceneManager& sceneManager = SceneManager::getInstance();
    sceneInfoDebugger.draw(sceneManager);
}

void DebugScene::finalize() {}

} // namespace Scene
