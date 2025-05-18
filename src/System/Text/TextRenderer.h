#pragma once

#include <string>

namespace Text {

class TextRenderer {
private:
    std::string fontName;
    int fontSize;

public:
    TextRenderer(const std::string& font, int size);
    ~TextRenderer() = default;

    void draw(int x, int y, const std::string& text, unsigned int color = 0xFFFFFFFF) const;
};

} // namespace Text
