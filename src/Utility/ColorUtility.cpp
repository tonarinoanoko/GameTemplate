#include "ColorUtility.h"
#include <DxLib.h>

namespace Utility {

const unsigned int Color::White   = GetColor(255, 255, 255);
const unsigned int Color::Black   = GetColor(  0,   0,   0);
const unsigned int Color::Red     = GetColor(255,   0,   0);
const unsigned int Color::Green   = GetColor(  0, 255,   0);
const unsigned int Color::Blue    = GetColor(  0,   0, 255);
const unsigned int Color::Yellow  = GetColor(255, 255,   0);
const unsigned int Color::Magenta = GetColor(255,   0, 255);
const unsigned int Color::Cyan    = GetColor(  0, 255, 255);

} // namespace Utility
