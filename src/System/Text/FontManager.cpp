#include "FontManager.h"
#include "System/Log/Logger.h"

namespace Text {

FontManager* FontManager::instance = nullptr;

FontManager::FontManager() {}

FontManager::~FontManager() {
    releaseAllFonts();
}

FontManager& FontManager::getInstance() {
    if (!instance) {
        instance = new FontManager();
    }
    return *instance;
}

bool FontManager::loadFont(const std::string& fontName, int size, int thick, bool antiAliasing, int charSet) {
    if (fontHandles.find(fontName) == fontHandles.end()) {
        int handle = CreateFontToHandle(fontName.c_str(), size, thick, antiAliasing ? DX_FONTTYPE_ANTIALIASING : DX_FONTTYPE_NORMAL, charSet);
        if (handle == -1) {
            LOGGER_ERROR("Failed to load font: %s, size: %d", fontName.c_str(), size);
            return false;
        }
        fontHandles[fontName] = handle;
        LOGGER_DEBUG("Font loaded: %s, size: %d, handle: %d", fontName.c_str(), size, handle);
        return true;
    } else {
        LOGGER_WARNING("Font already loaded: %s", fontName.c_str());
        return true;
    }
}

int FontManager::getFontHandle(const std::string& fontName) const {
    auto it = fontHandles.find(fontName);
    if (it != fontHandles.end()) {
        return it->second;
    }
    LOGGER_ERROR("Font not found: %s", fontName.c_str());
    return -1;
}

void FontManager::releaseAllFonts() {
    for (auto const& [fontName, handle] : fontHandles) {
        DeleteFontToHandle(handle);
        LOGGER_DEBUG("Font released: %s, handle: %d", fontName.c_str(), handle);
    }
    fontHandles.clear();
    LOGGER_INFO("All fonts released.");
}

} // namespace Text
