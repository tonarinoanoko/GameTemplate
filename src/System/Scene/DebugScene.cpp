#include "DebugScene.h"
#include <DxLib.h>
#include "System/Scene/SceneManager.h"
#include "System/Input/InputManager.h"
#include "Utility/ColorUtility.h" // ColorUtility のインクルード


namespace Scene {

DebugScene::DebugScene() {}

void DebugScene::initialize()
{
}

void DebugScene::update()
{
    if (Input::InputManager::getInstance().isKeyPressed(KEY_INPUT_I))
    {
        _scene_info_debugger.setVisible(_scene_info_debugger.visible() == false);
    }
}

void DebugScene::draw()
{
    DrawString(10, 10, "Debug Mode", COLOR_WHITE);
    DrawString(10, 30, "Press 'I' to toggle Scene Info", COLOR_WHITE);

    auto const& scene_manager = SceneManager::instance();
    _scene_info_debugger.draw(scene_manager);
}

void DebugScene::finalize()
{
}

} // namespace Scene
