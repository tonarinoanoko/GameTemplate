#pragma once

#include <vector>
#include <string>
#include "TextData.h"

namespace Text {

class MultiTextRenderer {
private:
    std::string fontName;
    int fontSize;
    std::vector<const TextData*> textDataPointers;

public:
    MultiTextRenderer(const std::string& font, int size);
    ~MultiTextRenderer();

    // TextData の参照を渡すバージョン
    void addTextData(const TextData* textData);

    // 個別の値を渡すバージョン
    void addText(int x, int y, const std::string& text, unsigned int color = 0xFFFFFFFF);

    void clearTexts();
    void drawAll() const;
};

} // namespace Text
