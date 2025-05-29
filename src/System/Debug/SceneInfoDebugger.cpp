#include "SceneInfoDebugger.h"
#include "System/Scene/SceneManager.h"
#include "Utility/ColorUtility.h"
#include <DxLib.h>

namespace Debug {

SceneInfoDebugger::SceneInfoDebugger() {}

void SceneInfoDebugger::setVisible(bool visible) {
    _visible = visible;
}

void SceneInfoDebugger::draw(const Scene::SceneManager& scene_manager) {
    if (_visible) {
        std::string scene_name = scene_manager.currentSceneName();
        DrawString(10, 50, ("Current Scene: " + scene_name).c_str(), COLOR_YELLOW);
    }
}

} // namespace Debug
