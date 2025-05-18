#pragma once

#include <string>
#include <memory>

namespace Graphics {

class TextureLoader; // forward declaration

class Graphics {
private:
    int textureHandle = -1;
    int x = 0;
    int y = 0;
    int width = 0;
    int height = 0;
    std::string filePath;
    std::weak_ptr<TextureLoader> loader; // ローダーへの弱い参照

public:
    Graphics(const std::string& path, int handle, const std::shared_ptr<TextureLoader>& loaderPtr);
    ~Graphics();

    int getTextureHandle() const { return textureHandle; }
    int getX() const { return x; }
    int getY() const { return y; }
    int getWidth() const { return width; }
    int getHeight() const { return height; }
    const std::string& getFilePath() const { return filePath; }

    void setPosition(int newX, int newY);
    void draw() const;

    void releaseTexture(); // テクスチャを解放する
    bool isTextureValid() const { return textureHandle != -1; }

private:
    // コピーコンストラクタとコピー代入演算子の削除
    Graphics(const Graphics&) = delete;
    Graphics& operator=(const Graphics&) = delete;
};

} // namespace Graphics
