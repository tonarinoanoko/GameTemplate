#include "GraphicsManager.h"
#include "System/Debug/Log/Logger.h"

namespace Graphics {

GraphicsManager::GraphicsManager() {}

std::shared_ptr<Graphics> GraphicsManager::loadGraphics(const std::string& filePath) {
    auto it = loaders.find(filePath);
    std::shared_ptr<TextureLoader> loaderPtr;

    if (it != loaders.end()) {
        loaderPtr = it->second;
        loaderPtr->incrementUseCount();
        Log::Logger::getInstance().debug("Using existing loader for: %s, Count: %d", filePath.c_str(), loaderPtr->getUseCount());
    } else {
        loaderPtr = std::make_shared<TextureLoader>(filePath);
        loaderPtr->load();
        loaders[filePath] = loaderPtr;
        Log::Logger::getInstance().debug("Created new loader for: %s, Handle: %d, Count: %d", filePath.c_str(), loaderPtr->getTextureHandle(), loaderPtr->getUseCount());
    }

    if (loaderPtr->getTextureHandle() != -1) {
        return std::make_shared<Graphics>(filePath, loaderPtr->getTextureHandle(), loaderPtr);
    }
    return nullptr;
}

void GraphicsManager::releaseGraphics(const std::shared_ptr<Graphics>& graphics) {
    if (graphics) {
        graphics->releaseTexture(); // Graphics 側のテクスチャ解放処理を呼ぶ
        const std::string& filePath = graphics->getFilePath();
        auto it = loaders.find(filePath);
        if (it != loaders.end()) {
            // ローダーの使用カウントが0になったら破棄 (オプション)
            if (it->second->getUseCount() <= 0) {
                loaders.erase(it);
                LOGGER_DEBUG("Loader removed for: %s", filePath.c_str());
            }
        }
    }
}

} // namespace Graphics
