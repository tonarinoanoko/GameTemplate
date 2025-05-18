#include "ResourceManager.h"
#include "System/Log/Logger.h"

namespace Graphics {

ResourceManager* ResourceManager::instance = nullptr;

ResourceManager::ResourceManager() {}

ResourceManager& ResourceManager::getInstance() {
    if (!instance) {
        instance = new ResourceManager();
    }
    return *instance;
}

std::shared_ptr<Graphics> ResourceManager::loadGraphics(const std::string& filePath) {
    auto it = loaders.find(filePath);
    std::shared_ptr<TextureLoader> loaderPtr;

    if (it != loaders.end()) {
        loaderPtr = it->second;
        loaderPtr->incrementUseCount();
        LOGGER_DEBUG("ResourceManager: Using existing loader for: %s, Count: %d", filePath.c_str(), loaderPtr->getUseCount());
    } else {
        loaderPtr = std::make_shared<TextureLoader>(filePath);
        loaderPtr->load();
        loaders[filePath] = loaderPtr;
        LOGGER_DEBUG("ResourceManager: Created new loader for: %s, Handle: %d, Count: %d", filePath.c_str(), loaderPtr->getTextureHandle(), loaderPtr->getUseCount());
    }

    if (loaderPtr->getTextureHandle() != -1) {
        return std::make_shared<Graphics>(filePath, loaderPtr->getTextureHandle(), loaderPtr);
    }
    return nullptr;
}

void ResourceManager::releaseGraphics(const std::shared_ptr<Graphics>& graphics) {
    if (graphics) {
        graphics->releaseTexture();
        const std::string& filePath = graphics->getFilePath();
        auto it = loaders.find(filePath);
        if (it != loaders.end()) {
            if (it->second->getUseCount() <= 0) {
                loaders.erase(it);
                LOGGER_DEBUG("ResourceManager: Loader removed for: %s", filePath.c_str());
            }
        }
    }
}

bool ResourceManager::isResourceLoaded(const std::string& filePath) const {
    return loaders.count(filePath) > 0;
}

std::shared_ptr<TextureLoader> ResourceManager::getLoader(const std::string& filePath) const {
    auto it = loaders.find(filePath);
    if (it != loaders.end()) {
        return it->second;
    }
    return nullptr;
}

} // namespace Graphics
