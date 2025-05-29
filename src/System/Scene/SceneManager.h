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
    static SceneManager& getInstance();

    void addPersistentScene(std::unique_ptr<SceneBase> scene);
    void addScene(std::unique_ptr<SceneBase> scene);
    void removeScene(SceneBase* scene);

    void startFadeIn(std::unique_ptr<SceneBase> nextScene, float duration);
    void startFadeOut(float duration);
    bool isFading() const { return fadeScene != nullptr; }

    // 現在表示中のシーン名を取得
    std::string getCurrentSceneName() const;

    void update();
    void draw();

private:
    static SceneManager* instance;
    SceneManager();
    ~SceneManager() = default;
    SceneManager(const SceneManager&) = delete;
    SceneManager& operator=(const SceneManager&) = delete;

    std::vector<std::unique_ptr<SceneBase>> persistentScenes;
    std::vector<std::unique_ptr<SceneBase>> activeScenes;
    std::unique_ptr<FadeScene> fadeScene;
    std::unique_ptr<SceneBase> debugScene;
};

} // namespace Scene
