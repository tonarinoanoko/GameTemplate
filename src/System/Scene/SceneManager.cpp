#include "SceneManager.h"
#include <algorithm>
#include "PauseScene.h"

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

void SceneManager::setDebugMode(bool debugMode) {
    isDebugMode = debugMode;
    if (isDebugMode && !debugScene) {
        // debugScene は別途実装
        // debugScene = std::make_unique<DebugScene>();
        // debugScene->initialize();
    } else if (!isDebugMode && debugScene) {
        debugScene->finalize();
        debugScene.reset();
    }
}

void SceneManager::pauseGame() {
    if (!isPaused) {
        isPaused = true;
        for (const auto& scene : activeScenes) {
            if (scene->isPausingEnabled()) {
                scene->onPause();
            }
        }
        if (pauseScene) {
            pauseScene->initialize();
        }
    }
}

void SceneManager::resumeGame() {
    if (isPaused) {
        isPaused = false;
        for (const auto& scene : activeScenes) {
            if (scene->isPausingEnabled()) {
                scene->onResume();
            }
        }
        if (pauseScene) {
            pauseScene->finalize();
            pauseScene.reset();
        }
    }
}

void SceneManager::setPauseScene(std::unique_ptr<SceneBase> scene) {
    pauseScene = std::move(scene);
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
    } else if (!isPaused) {
        // ポーズ中でなければアクティブシーンを更新
        for (const auto& scene : activeScenes) {
            if (scene->isPausingEnabled()) {
                scene->update();
            }
        }
    }

    // デバッグシーンの更新
    if (isDebugMode && debugScene) {
        debugScene->update();
    }

    // ポーズメニューシーンの更新
    if (isPaused && pauseScene) {
        pauseScene->update();
    }
}

void SceneManager::draw() {
    // 常駐シーンの描画
    for (const auto& scene : persistentScenes) {
        scene->draw();
    }

    // アクティブシーンの描画 (ポーズ中でなく、デバッグモードでない場合)
    if (!isPaused && !isDebugMode) {
        for (const auto& scene : activeScenes) {
            scene->draw();
        }
    } else if (isDebugMode) {
        // デバッグモードの場合、アクティブシーンを描画
        for (const auto& scene : activeScenes) {
            scene->draw();
        }
        if (debugScene) {
            debugScene->draw();
        }
    } else if (isPaused) {
        // ポーズ中のアクティブシーンの描画 (少し暗くするなど)
        //SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128); // 半透明で暗くする例
        for (const auto& scene : activeScenes) {
            scene->draw();
        }
        //SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
        // ポーズメニューシーンの描画
        if (pauseScene) {
            pauseScene->draw();
        }
    }

    // フェードシーンの描画 (最前面)
    if (fadeScene) {
        fadeScene->draw();
    }
}

std::string SceneManager::getCurrentSceneName() const {
    if (!activeScenes.empty()) {
        // typeid を使用して型名を取得し、不要な情報を削除
        std::string name = typeid(*activeScenes.back()).name();
        // Visual Studio の場合 "__1?AV" で始まり、末尾に "@@YAAXXZ" などが付く
        size_t startPos = name.find_first_not_of(" _?AV");
        if (std::string::npos != startPos) {
            name = name.substr(startPos);
        }
        size_t endPos = name.find("@@");
        if (std::string::npos != endPos) {
            name = name.substr(0, endPos);
        }
        return name;
    }
    return "No Active Scene";
}

} // namespace Scene
