#pragma once

#include <DxLib.h>

namespace Utility {

class Color {
public:
    static const unsigned int White;
    static const unsigned int Black;
    static const unsigned int Red;
    static const unsigned int Green;
    static const unsigned int Blue;
    static const unsigned int Yellow;
    static const unsigned int Magenta;
    static const unsigned int Cyan;
};

} // namespace Utility

// マクロ定義 (ColorUtility.h の末尾に追加)
#define COLOR_WHITE (Utility::Color::White)
#define COLOR_BLACK (Utility::Color::Black)
#define COLOR_RED (Utility::Color::Red)
#define COLOR_GREEN (Utility::Color::Green)
#define COLOR_BLUE (Utility::Color::Blue)
#define COLOR_YELLOW (Utility::Color::Yellow)
#define COLOR_MAGENTA (Utility::Color::Magenta)
#define COLOR_CYAN (Utility::Color::Cyan)
