#pragma once

#include <map>
#include <string>
#include <memory>
#include "DxLib.h"

namespace Text {

class FontManager {
private:
    static FontManager* instance;
    FontManager();
    ~FontManager();
    FontManager(const FontManager&) = delete;
    FontManager& operator=(const FontManager&) = delete;

    std::map<std::string, int> fontHandles;

public:
    static FontManager& getInstance();

    bool loadFont(const std::string& fontName, int size, int thick = 0, bool antiAliasing = TRUE, int charSet = DX_CHARSET_DEFAULT);
    int getFontHandle(const std::string& fontName) const;
    void releaseAllFonts();
};

} // namespace Text
