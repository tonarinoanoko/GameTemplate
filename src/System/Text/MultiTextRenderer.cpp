#include "MultiTextRenderer.h"
#include "FontManager.h"
#include "TextData.h"
#include "DxLib.h"

#include "System/Log/Logger.h"

namespace Text {

MultiTextRenderer::MultiTextRenderer(const std::string& font, int size) : fontName(font), fontSize(size) {
    if (FontManager::getInstance().getFontHandle(fontName) == -1) {
        LOGGER_ERROR("Font not loaded before MultiTextRenderer creation: %s", fontName.c_str());
    }
}

MultiTextRenderer::~MultiTextRenderer() {
    clearTexts(); // デストラクタでも確保したメモリを解放
}

void MultiTextRenderer::addTextData(const TextData* textData) {
    textDataPointers.push_back(textData);
}

void MultiTextRenderer::addText(int x, int y, const std::string& text, unsigned int color) {
    // 内部で TextData のインスタンスを作成してポインタを保持
    TextData* newData = new TextData{x, y, text, color};
    textDataPointers.push_back(newData);
}

void MultiTextRenderer::clearTexts() {
    // 値渡しで追加された TextData を削除
    for (const auto* ptr : textDataPointers) {
        delete ptr;
    }
    textDataPointers.clear();
}

void MultiTextRenderer::drawAll() const {
    int fontHandle = FontManager::getInstance().getFontHandle(fontName);
    if (fontHandle != -1) {
        for (const auto* textData : textDataPointers) {
            if (textData) {
                DrawStringToHandle(textData->x, textData->y, textData->text.c_str(), textData->color, fontHandle);
            }
        }
    }
}

} // namespace Text
