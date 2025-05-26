#include "SceneGraphicsManager.h"
#include "ResourceManager.h"
#include "System/Debug/Log/Logger.h"

namespace Graphics {

SceneGraphicsManager::SceneGraphicsManager() {}

std::shared_ptr<Graphics> SceneGraphicsManager::loadGraphics(const std::string& filePath) {
    // まず常駐マネージャーにロード済みか確認
    ResourceManager& resourceManager = ResourceManager::getInstance();
    if (resourceManager.isResourceLoaded(filePath)) {
        LOGGER_DEBUG("SceneGraphicsManager: Using resource from ResourceManager for: %s", filePath.c_str());
        std::shared_ptr<TextureLoader> loaderPtr = resourceManager.getLoader(filePath);
        if (loaderPtr) {
            loaderPtr->incrementUseCount();
            return std::make_shared<Graphics>(filePath, loaderPtr->getTextureHandle(), loaderPtr);
        }
    }

    // 常駐マネージャーにない場合は、シーン専用にロード
    auto it = loaders.find(filePath);
    std::shared_ptr<TextureLoader> loaderPtr;

    if (it != loaders.end()) {
        loaderPtr = it->second;
        loaderPtr->incrementUseCount();
        LOGGER_DEBUG("SceneGraphicsManager: Using existing loader for: %s, Count: %d", filePath.c_str(), loaderPtr->getUseCount());
    } else {
        loaderPtr = std::make_shared<TextureLoader>(filePath);
        loaderPtr->load();
        loaders[filePath] = loaderPtr;
        LOGGER_DEBUG("SceneGraphicsManager: Created new loader for: %s, Handle: %d, Count: %d", filePath.c_str(), loaderPtr->getTextureHandle(), loaderPtr->getUseCount());
    }

    if (loaderPtr->getTextureHandle() != -1) {
        return std::make_shared<Graphics>(filePath, loaderPtr->getTextureHandle(), loaderPtr);
    }
    return nullptr;
}

void SceneGraphicsManager::releaseGraphics(const std::shared_ptr<Graphics>& graphics) {
    if (graphics) {
        graphics->releaseTexture();
        const std::string& filePath = graphics->getFilePath();

        // まずシーン専用のローダーから探す
        auto it = loaders.find(filePath);
        if (it != loaders.end()) {
            if (it->second->getUseCount() <= 0) {
                loaders.erase(it);
                LOGGER_DEBUG("SceneGraphicsManager: Loader removed for: %s", filePath.c_str());
            }
        } else {
            // シーン専用になければ常駐マネージャーのローダーの可能性
            ResourceManager& resourceManager = ResourceManager::getInstance();
            if (resourceManager.isResourceLoaded(filePath)) {
                if (auto loaderPtr = resourceManager.getLoader(filePath)) {
                    loaderPtr->decrementUseCount();
                    LOGGER_DEBUG("SceneGraphicsManager: Released resource used from ResourceManager for: %s, Count: %d", filePath.c_str(), loaderPtr->getUseCount());
                }
            }
        }
    }
}

} // namespace Graphics
