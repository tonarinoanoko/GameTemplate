#include "SceneInfoDebugger.h"
#include "System/Scene/SceneManager.h"
#include <DxLib.h>

namespace Debug {

SceneInfoDebugger::SceneInfoDebugger() {}

void SceneInfoDebugger::setVisible(bool visible) {
    isVisible = visible;
}

void SceneInfoDebugger::draw(const Scene::SceneManager& sceneManager) {
    if (isVisible) {
        std::string currentSceneName = sceneManager.getCurrentSceneName();
        DrawString(10, 50, ("Current Scene: " + currentSceneName).c_str(), GetColor(255, 255, 0));
    }
}

} // namespace Debug
