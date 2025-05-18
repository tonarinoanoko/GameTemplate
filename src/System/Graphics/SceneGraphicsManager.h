#pragma once

#include <map>
#include <string>
#include <memory>
#include "Graphics.h"
#include "TextureLoader.h"
#include "ResourceManager.h" // 常駐マネージャーへのアクセス

namespace Graphics {

class SceneGraphicsManager {
private:
    std::map<std::string, std::shared_ptr<TextureLoader>> loaders;

public:
    SceneGraphicsManager();
    ~SceneGraphicsManager() = default;

    std::shared_ptr<Graphics> loadGraphics(const std::string& filePath);
    void releaseGraphics(const std::shared_ptr<Graphics>& graphics);
};

} // namespace Graphics
