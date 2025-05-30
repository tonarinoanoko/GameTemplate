#include "SceneManager.h"
#include <algorithm>
#include "DxLib.h"
#include "DebugScene.h"

namespace Scene {

SceneManager::SceneManager()
{
    _fade_scene = std::make_unique<FadeScene>();
    _fade_scene->initialize();
    _debug_scene = std::make_unique<DebugScene>();
    _debug_scene->initialize();
}

SceneManager& SceneManager::instance()
{
    static SceneManager _instance;
    return _instance;
}

void SceneManager::addResidentScene(std::unique_ptr<SceneBase> scene)
{
    if (scene) {
        scene->initialize();
        _resident_scene.push_back(std::move(scene));
    }
}

void SceneManager::addScene(std::unique_ptr<SceneBase> scene)
{
    if (scene) {
        scene->initialize();
        _active_scenes.push_back(std::move(scene));
    }
}

void SceneManager::removeScene(SceneBase* scene)
{
    _active_scenes.erase(std::remove_if(_active_scenes.begin(), _active_scenes.end(),
                                    [&](const std::unique_ptr<SceneBase>& s)
                                    {
                                        if (s.get() == scene) {
                                            s->finalize(); // 削除する前に finalize を呼び出す
                                            return true;
                                        }
                                        return false;
                                    }),
                                    _active_scenes.end());
}

void SceneManager::startFadeIn(float duration)
{
    if (_fade_scene) {
        _fade_scene->setFade(FadeScene::eMode::In, duration);
    }
}

void SceneManager::startFadeOut(float duration)
{
    if (_fade_scene) {
        _fade_scene->setFade(FadeScene::eMode::Out, duration);
    }
}

void SceneManager::update()
{
    // 常駐シーンの更新
    for (const auto& scene : _resident_scene) {
        scene->update();
    }

    // 基本シーンの更新
    for (const auto& scene : _active_scenes) {
        scene->update();
    }

    // デバッグシーンの更新
    if (_debug_scene) {
        _debug_scene->update();
    }

    // フェードシーンの更新
    if (_fade_scene) {
        _fade_scene->update();
    }
}

void SceneManager::draw()
{
    for (const auto& scene : _resident_scene) {
        scene->draw();
    }

    for (const auto& scene : _active_scenes) {
        scene->draw();
    }

    if (_debug_scene) {
        _debug_scene->draw();
    }

    // フェードシーンの描画 (最前面)
    if (_fade_scene) {
        _fade_scene->draw();
    }
}

std::string SceneManager::currentSceneName() const
{
    if (_active_scenes.empty() == false) {
        std::string name = typeid(*_active_scenes.back()).name();
        return name;
    }
    return "No Active Scene";
}

} // namespace Scene
