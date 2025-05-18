#pragma once

namespace Math {

class Rect {
public:
    int x;
    int y;
    int width;
    int height;

    Rect();
    Rect(int x, int y, int width, int height);
    Rect(const Rect& other);
    Rect& operator=(const Rect& other);
    bool operator==(const Rect& other) const;

    // 未衝突判定
    bool isNotCollidingWith(const Rect& other) const;

    // 一部衝突判定
    bool isPartiallyCollidingWith(const Rect& other) const;

    // 全衝突判定 (other が this を完全に包含しているか)
    bool isCompletelyCollidingWith(const Rect& other) const;

    // 全包含判定 (this が other を完全に包含しているか)
    bool completelyContains(const Rect& other) const;
};

} // namespace Math
