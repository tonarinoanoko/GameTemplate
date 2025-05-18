#pragma once

#include "SceneBase.h"

namespace Scene {

class PauseScene : public SceneBase {
public:
    PauseScene();
    ~PauseScene() override = default;

    void initialize() override;
    void update() override;
    void draw() override;
    void finalize() override;
};

} // namespace Scene
