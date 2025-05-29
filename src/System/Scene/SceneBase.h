#pragma once

namespace Scene {

class SceneBase {
public:
    virtual ~SceneBase() = default;

    virtual void initialize() = 0;
    virtual void update() = 0;
    virtual void draw() = 0;
    virtual void finalize() = 0;

    virtual bool isPersistent() const { return false; }    // 常駐シーンかどうか
    virtual void onPause() {}                              // ポーズ時に呼ばれる (デフォルトは何もしない)
    virtual void onResume() {}                             // ポーズ解除時に呼ばれる (デフォルトは何もしない)
    virtual bool isPausingEnabled() const { return true; } // ポーズ可能かどうか (デフォルトは可能)
};

} // namespace Scene
