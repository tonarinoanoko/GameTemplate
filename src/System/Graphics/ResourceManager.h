#pragma once

#include <map>
#include <string>
#include <memory>
#include "Graphics.h"
#include "TextureLoader.h"

namespace Graphics {

class ResourceManager {
private:
    static ResourceManager* instance;
    ResourceManager();
    ~ResourceManager() = default;
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;

    std::map<std::string, std::shared_ptr<TextureLoader>> loaders;

public:
    static ResourceManager& getInstance();

    std::shared_ptr<Graphics> loadGraphics(const std::string& filePath);
    void releaseGraphics(const std::shared_ptr<Graphics>& graphics);

    // ローダーが存在するか確認 (シーン専用マネージャーからの問い合わせ用)
    bool isResourceLoaded(const std::string& filePath) const;
    std::shared_ptr<TextureLoader> getLoader(const std::string& filePath) const;
};

} // namespace Graphics
