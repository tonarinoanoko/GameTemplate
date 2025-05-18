#pragma once

#include <string>

namespace Graphics {

class TextureLoader {
private:
    std::string filePath;
    int textureHandle = -1;
    int useCount = 0;

public:
    TextureLoader(const std::string& path);
    ~TextureLoader();

    int load();
    void incrementUseCount();
    void decrementUseCount();
    int getTextureHandle() const { return textureHandle; }
    const std::string& getFilePath() const { return filePath; }
    int getUseCount() const { return useCount; }

private:
    // コピーコンストラクタとコピー代入演算子の削除
    TextureLoader(const TextureLoader&) = delete;
    TextureLoader& operator=(const TextureLoader&) = delete;
};

} // namespace Graphics
