#include "FadeScene.h"
#include <DxLib.h>


namespace Scene {

FadeScene::FadeScene(eMode mode, float duration) : mode(mode), duration(duration), currentTime(0.0f) {}

void FadeScene::initialize() {
    // 必要に応じて初期化処理
}

void FadeScene::update() {
    currentTime += 1.0f / GetFPS(); // フレームレートに依存しない更新
    if (currentTime > duration) {
        currentTime = duration;
    }
}

void FadeScene::draw() {
    int alpha = 0;
    if (mode == eMode::In) {
        alpha = static_cast<int>((1.0f - currentTime / duration) * 255);
    } else if (mode == eMode::Out) {
        alpha = static_cast<int>((currentTime / duration) * 255);
    }
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
    DrawBox(0, 0, 640, 480, GetColor(0, 0, 0), TRUE); // 画面全体を黒で描画
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

} // namespace Scene
