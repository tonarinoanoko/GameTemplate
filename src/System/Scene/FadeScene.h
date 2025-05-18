#pragma once

#include "SceneBase.h"

namespace Scene {

class FadeScene : public SceneBase {
public:
    enum class eMode {
        In,
        Out
    };

private:
    eMode mode;
    float duration;
    float currentTime;

public:
    FadeScene(eMode mode, float duration);
    ~FadeScene() override = default;

    void initialize() override;
    void update() override;
    void draw() override;
    void finalize() override {}

    bool isFinished() const { return currentTime >= duration; }
    eMode getMode() const { return mode; }
};

} // namespace Scene
