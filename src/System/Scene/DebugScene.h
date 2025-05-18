#pragma once

#include "SceneBase.h"
#include "System/Debug/SceneInfoDebugger.h" // デバッガークラスのインクルード

namespace Scene {

class DebugScene : public SceneBase {
private:
    Debug::SceneInfoDebugger sceneInfoDebugger;

public:
    DebugScene();
    ~DebugScene() override = default;

    void initialize() override;
    void update() override;
    void draw() override;
    void finalize() override;
};

} // namespace Scene
