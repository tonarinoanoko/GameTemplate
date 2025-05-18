#pragma once

#include <string>

namespace Scene {
    class SceneManager;
}

namespace Debug {

class SceneInfoDebugger {
private:
    bool isVisible = true;

public:
    SceneInfoDebugger();
    void setVisible(bool visible);
    void draw(const Scene::SceneManager& sceneManager);
    bool visible() { return isVisible; }
};

} // namespace Debug
