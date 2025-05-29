#pragma once

#include "SceneBase.h"
#include "System/Debug/SceneInfoDebugger.h"

namespace Scene {

class DebugScene : public SceneBase
{
public:
    DebugScene();
    ~DebugScene() override = default;

    void initialize() override;
    void update() override;
    void draw() override;
    void finalize() override;

private:
    Debug::SceneInfoDebugger _scene_info_debugger;
};

}  // namespace Scene
