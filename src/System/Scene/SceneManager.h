#pragma once

#include <vector>
#include <memory>
#include <string>
#include "SceneBase.h"
#include "FadeScene.h"

namespace Scene {

class SceneManager
{
public:
    static SceneManager& instance();

    void addResidentScene(std::unique_ptr<SceneBase> scene);
    void addScene(std::unique_ptr<SceneBase> scene);
    void removeScene(SceneBase* scene);

    void startFadeIn(float duration);
    void startFadeOut(float duration);
    bool isFading() const { return _fade_scene != nullptr; }

    // 現在表示中のシーン名を取得
    std::string currentSceneName() const;

    void update();
    void draw();

private:
    static SceneManager* _instance;
    SceneManager();
    ~SceneManager() = default;
    SceneManager(SceneManager const&) = delete;
    SceneManager& operator=(SceneManager const&) = delete;

    std::vector<std::unique_ptr<SceneBase>> _resident_scene;
    std::vector<std::unique_ptr<SceneBase>> _active_scenes;
    std::unique_ptr<FadeScene> _fade_scene;
    std::unique_ptr<SceneBase> _debug_scene;
};

} // namespace Scene
