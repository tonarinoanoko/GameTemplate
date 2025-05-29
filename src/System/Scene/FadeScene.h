#pragma once

#include "SceneBase.h"

namespace Scene {
class FadeScene : public SceneBase
{
public:
    enum class eMode {
        None,
        In,
        Out
    };

public:
    FadeScene();
    ~FadeScene() override = default;

    void initialize() override;
    void update() override;
    void draw() override;
    void finalize() override {}

    void setFade(eMode mode, float duration);
    bool isFinished() const;
    eMode mode() const { return _mode; }

private:
    eMode _mode;
    float _duration;
    float _current_time;
};

} // namespace Scene
