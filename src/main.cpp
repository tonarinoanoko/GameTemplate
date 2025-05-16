#include <iostream>
#include <DxLib.h>

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
