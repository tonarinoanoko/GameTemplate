#include "Rect.h"

namespace Math {

Rect::Rect() : x(0), y(0), width(0), height(0) {}
Rect::Rect(int x, int y, int width, int height) : x(x), y(y), width(width), height(height) {}
Rect::Rect(const Rect& other) : x(other.x), y(other.y), width(other.width), height(other.height) {}

Rect& Rect::operator=(const Rect& other) {
    if (this != &other) {
        x = other.x;
        y = other.y;
        width = other.width;
        height = other.height;
    }
    return *this;
}

bool Rect::operator==(const Rect& other) const {
    return (x == other.x && y == other.y && width == other.width && height == other.height);
}

bool Rect::isNotCollidingWith(const Rect& other) const {
    return (x + width <= other.x ||
            other.x + other.width <= x ||
            y + height <= other.y ||
            other.y + other.height <= y);
}

bool Rect::isPartiallyCollidingWith(const Rect& other) const {
    return !isNotCollidingWith(other);
}

bool Rect::isCompletelyCollidingWith(const Rect& other) const {
    return (other.x >= x &&
            other.x + other.width <= x + width &&
            other.y >= y &&
            other.y + other.height <= y + height);
}

bool Rect::completelyContains(const Rect& other) const {
    return (x <= other.x &&
            x + width >= other.x + other.width &&
            y <= other.y &&
            y + height >= other.y + other.height);
}

} // namespace Math
