#include <iostream>
#include <DxLib.h>

#include "System/Input/InputManager.h" // InputManager クラスのヘッダーをインクルード

System::InputManager inputManager; // InputManager のインスタンスを作成

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
    // DxLibの初期化
    if (DxLib_Init() == -1) {
        return -1; // 初期化に失敗したら終了
    }

    // ウィンドウモードに変更
    SetGraphMode(640, 480, 32);
    ChangeWindowMode(TRUE);

    // メインループ
    while (!ProcessMessage()) {

        // 入力マネージャーの更新
        inputManager.update();

        // 各キーの状態をチェックして処理を行う
        if (inputManager.isKeyPressed(KEY_INPUT_UP)) {
            std::cout << "UP key pressed!" << std::endl;
        }
        if (inputManager.isKeyHolding(KEY_INPUT_DOWN)) {
            std::cout << "DOWN key holding..." << std::endl;
        }
        if (inputManager.isKeyJustReleased(KEY_INPUT_LEFT)) {
            std::cout << "LEFT key just released." << std::endl;
        }
        if (inputManager.isKeyReleased(KEY_INPUT_RIGHT)) {
            // 何もしない (離されている状態)
        }
        if (inputManager.getState(KEY_INPUT_SPACE).isPressed()) { // getState() を直接使うことも可能
            std::cout << "SPACE key pressed (using getState)." << std::endl;
        }

        // 画面をクリア
        ClearDrawScreen();

        // ここにゲームの描画処理などを記述します

        // 画面を更新
        ScreenFlip();
    }

    // DxLibの終了処理
    DxLib_End();

    return 0;
}
