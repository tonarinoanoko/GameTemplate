#include "TextRenderer.h"
#include "FontManager.h"
#include "DxLib.h"
#include "System/Log/Logger.h"

namespace Text {

TextRenderer::TextRenderer(const std::string& font, int size) : fontName(font), fontSize(size) {
    // FontManager にフォントがロードされているか確認 (ロードされていなければエラー)
    if (FontManager::getInstance().getFontHandle(fontName) == -1) {
        LOGGER_ERROR("Font not loaded before TextRenderer creation: %s", fontName.c_str());
    }
}

void TextRenderer::draw(int x, int y, const std::string& text, unsigned int color) const {
    int fontHandle = FontManager::getInstance().getFontHandle(fontName);
    if (fontHandle != -1) {
        DrawStringToHandle(x, y, text.c_str(), color, fontHandle);
    }
}

} // namespace Text
