#include "Graphics.h"
#include <DxLib.h>
#include "TextureLoader.h"

namespace Graphics {

Graphics::Graphics(const std::string& path, int handle, const std::shared_ptr<TextureLoader>& loaderPtr)
    : textureHandle(handle), filePath(path), loader(loaderPtr) {
    GetGraphSize(textureHandle, &width, &height);
    if (auto sharedLoader = loader.lock()) {
        sharedLoader->incrementUseCount();
    }
}

Graphics::~Graphics() {
    releaseTexture();
}

void Graphics::setPosition(int newX, int newY) {
    x = newX;
    y = newY;
}

void Graphics::draw() const {
    if (textureHandle != -1) {
        DrawGraph(x, y, textureHandle, TRUE);
    }
}

void Graphics::releaseTexture() {
    if (textureHandle != -1) {
        if (auto sharedLoader = loader.lock()) {
            sharedLoader->decrementUseCount();
        }
        DeleteGraph(textureHandle);
        textureHandle = -1;
    }
}

} // namespace Graphics
