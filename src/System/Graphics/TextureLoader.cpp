#include "TextureLoader.h"
#include <DxLib.h>
#include "System/Debug/Log/Logger.h"

namespace Graphics {

TextureLoader::TextureLoader(const std::string& path) : filePath(path) {}

TextureLoader::~TextureLoader() {
    if (textureHandle != -1) {
        DeleteGraph(textureHandle);
        Log::Logger::getInstance().debug("Texture unloaded: %s", filePath.c_str());
        textureHandle = -1;
    }
}

int TextureLoader::load() {
    if (textureHandle == -1) {
        textureHandle = LoadGraph(filePath.c_str());
        if (textureHandle == -1) {
            Log::Logger::getInstance().error("Failed to load texture: %s", filePath.c_str());
        } else {
            Log::Logger::getInstance().debug("Texture loaded: %s, Handle: %d", filePath.c_str(), textureHandle);
        }
    }
    incrementUseCount();
    return textureHandle;
}

void TextureLoader::incrementUseCount() {
    useCount++;
}

void TextureLoader::decrementUseCount() {
    useCount--;
    Log::Logger::getInstance().debug("Use count decremented for: %s, Count: %d", filePath.c_str(), useCount);
    if (useCount <= 0 && textureHandle != -1) {
        // デストラクタに処理を移譲
    }
}

} // namespace Graphics
