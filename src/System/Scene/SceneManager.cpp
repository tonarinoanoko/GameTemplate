#include "SceneManager.h"
#include <algorithm>
#include "DxLib.h"
#include "DebugScene.h"

namespace Scene {

SceneManager* SceneManager::instance = nullptr;

SceneManager::SceneManager() {}

SceneManager& SceneManager::getInstance() {
    if (!instance) {
        instance = new SceneManager();
    }
    return *instance;
}

void SceneManager::addPersistentScene(std::unique_ptr<SceneBase> scene) {
    if (scene) {
        scene->initialize();
        persistentScenes.push_back(std::move(scene));
    }
}

void SceneManager::addScene(std::unique_ptr<SceneBase> scene) {
    if (scene) {
        scene->initialize();
        activeScenes.push_back(std::move(scene));
    }
}

void SceneManager::removeScene(SceneBase* scene) {
    activeScenes.erase(std::remove_if(activeScenes.begin(), activeScenes.end(),
                                      [&](const std::unique_ptr<SceneBase>& s){ return s.get() == scene; }),
                      activeScenes.end());
}

void SceneManager::startFadeIn(std::unique_ptr<SceneBase> nextScene, float duration) {
    if (!isFading() && nextScene) {
        this->addScene(std::move(nextScene));
        fadeScene = std::make_unique<FadeScene>(FadeScene::eMode::In, duration);
        fadeScene->initialize();
    }
}

void SceneManager::startFadeOut(float duration) {
    if (!isFading()) {
        fadeScene = std::make_unique<FadeScene>(FadeScene::eMode::Out, duration);
        fadeScene->initialize();
    }
}

void SceneManager::update() {
    // 常駐シーンの更新 (ポーズ中でも更新することがある)
    for (const auto& scene : persistentScenes) {
        scene->update();
    }

    // フェードシーンの更新
    if (fadeScene) {
        fadeScene->update();
        if (fadeScene->isFinished()) {
            fadeScene->finalize();
            fadeScene.reset();
            if (fadeScene->getMode() == FadeScene::eMode::Out) {
                activeScenes.clear();
            }
        }
    }
    else {
        for (const auto& scene : activeScenes) {
            if (scene->isPausingEnabled()) {
                scene->update();
            }
        }
    }

    // デバッグシーンの更新
    if (debugScene) {
        debugScene->update();
    }
}

void SceneManager::draw() {
    // 常駐シーンの描画
    for (const auto& scene : persistentScenes) {
        scene->draw();
    }

    for (const auto& scene : activeScenes) {
        scene->draw();
    }

    if (debugScene) {
        debugScene->draw();
    }

    // フェードシーンの描画 (最前面)
    if (fadeScene) {
        fadeScene->draw();
    }
}

std::string SceneManager::getCurrentSceneName() const {
    if (!activeScenes.empty()) {
        std::string name = typeid(*activeScenes.back()).name();
        return name;
    }
    return "No Active Scene";
}

} // namespace Scene
