#pragma once

#include <map>
#include <string>
#include <memory>
#include "Graphics.h"
#include "TextureLoader.h"

namespace Graphics {

class GraphicsManager {
private:
    std::map<std::string, std::shared_ptr<TextureLoader>> loaders;

public:
    GraphicsManager();
    ~GraphicsManager() = default;

    std::shared_ptr<Graphics> loadGraphics(const std::string& filePath);
    void releaseGraphics(const std::shared_ptr<Graphics>& graphics);

private:
    // コピーコンストラクタとコピー代入演算子の削除
    GraphicsManager(const GraphicsManager&) = delete;
    GraphicsManager& operator=(const GraphicsManager&) = delete;
};

} // namespace Graphics
