#pragma once

#include <vector>
#include <memory> // std::unique_ptr
#include <string>
#include "SceneBase.h"
#include "FadeScene.h"

namespace Scene {

class SceneManager {
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
    std::unique_ptr<SceneBase> pauseScene;
    bool isDebugMode = false;
    bool isPaused = false;

public:
    static SceneManager& getInstance();

    void addPersistentScene(std::unique_ptr<SceneBase> scene);
    void addScene(std::unique_ptr<SceneBase> scene);
    void removeScene(SceneBase* scene); // シーンのポインタで指定

    void startFadeIn(std::unique_ptr<SceneBase> nextScene, float duration);
    void startFadeOut(float duration);
    bool isFading() const { return fadeScene != nullptr; }

    void setDebugMode(bool debugMode);
    bool isDebugModeEnabled() const { return isDebugMode; }

    void pauseGame();
    void resumeGame();
    bool isGamePaused() const { return isPaused; }
    void setPauseScene(std::unique_ptr<SceneBase> scene); // ポーズメニューシーンの設定

    // 現在表示中のシーン名を取得
    std::string getCurrentSceneName() const;

    void update();
    void draw();
};

} // namespace Scene
