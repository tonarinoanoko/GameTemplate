#include <iostream>
#include <DxLib.h>
#include "System/Input/InputManager.h"
#include "System/Input/MouseInputManager.h"
#include "System/Log/Logger.h"
#include "System/Scene/SceneManager.h"
#include "System/Scene/DebugScene.h"
#include "System/Scene/PauseScene.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
    if (DxLib_Init() == -1) return -1;
    SetGraphMode(640, 480, 32);
    ChangeWindowMode(TRUE);

    Log::Logger::getInstance().setLogLevel(Log::eLogLevel::Debug);
    Scene::SceneManager& sceneManager = Scene::SceneManager::getInstance();
    sceneManager.setPauseScene(std::make_unique<Scene::PauseScene>());

    bool debugModeEnabled = false;

    while (!ProcessMessage()) {
        Input::InputManager::getInstance().update();
        Input::MouseInputManager::getInstance().update();

        if (Input::InputManager::getInstance().isKeyPressed(KEY_INPUT_D)) {
            debugModeEnabled = !debugModeEnabled;
            sceneManager.setDebugMode(debugModeEnabled);
            LOGGER_INFO("Debug Mode : %s", debugModeEnabled ? "ON" : "OFF");
        }

        if (Input::InputManager::getInstance().isKeyPressed(KEY_INPUT_P) && !sceneManager.isFading()) {
            sceneManager.isGamePaused() ? sceneManager.resumeGame() : sceneManager.pauseGame();
        }

        if (Input::InputManager::getInstance().isKeyPressed(KEY_INPUT_SPACE) && !sceneManager.isFading() && !sceneManager.isGamePaused()) {
            sceneManager.startFadeOut(1.0f);
        }

        sceneManager.update();

        ClearDrawScreen();
        sceneManager.draw();
        ScreenFlip();
    }

    DxLib_End();
    return 0;
}
