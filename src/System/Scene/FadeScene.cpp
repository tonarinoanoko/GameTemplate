#include "FadeScene.h"
#include <DxLib.h>
#include "Utility/ColorUtility.h"

namespace Scene {

FadeScene::FadeScene() :
    _mode(eMode::None),
    _duration(0.0f),
    _current_time(0.0f)
{
}

void FadeScene::initialize()
{
}

void FadeScene::setFade(eMode mode, float duration)
{
    _mode = mode;
    _duration = duration;
    _current_time = 0.0f;
}

void FadeScene::update() {
    if(_mode == eMode::None) {
        return;
    }

    _current_time += 1.0f / GetFPS();
    if (_current_time > _duration) {
        _current_time = _duration;
    }
}

void FadeScene::draw()
{
    if(_mode == eMode::None) {
        return;
    }

    int alpha = 0;
    if (_mode == eMode::In) {
        alpha = static_cast<int>((1.0f - _current_time / _duration) * 255);
    }
    else if (_mode == eMode::Out) {
        alpha = static_cast<int>((_current_time / _duration) * 255);
    }
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
    DrawBox(0, 0, 640, 480, COLOR_BLACK, TRUE); // 画面全体を黒で描画
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

bool FadeScene::isFinished() const
{
    return _current_time >= _duration;
}

} // namespace Scene
