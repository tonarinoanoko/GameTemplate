#pragma once

#include <string>

namespace Scene {
    class SceneManager;
}

namespace Debug {

class SceneInfoDebugger
{
public:
    SceneInfoDebugger();
    void setVisible(bool visible);
    void draw(const Scene::SceneManager& scene_manager);
    bool visible() { return _visible; }

private:
    bool _visible = true;
};

}  // namespace Debug
