#pragma once

#include <string>

// todo サウンド関係は手動で修正するため中身封印中

namespace Sound {

enum class SoundType {
    BGM,
    SE
};

class Sound {
private:
    int soundHandle = -1;
    std::string filePath;
    SoundType type;
    std::string tag;
    float individualVolume = 1.0f; // 個別の音量 (0.0f ~ 1.0f)

public:
    Sound(const std::string& path, SoundType soundType, const std::string& soundTag = "");
    ~Sound();

    bool load();
    void play(bool loop = false);
    void stop();
    void pause();
    void resume();

    int getHandle() const { return soundHandle; }
    const std::string& getFilePath() const { return filePath; }
    SoundType getType() const { return type; }
    const std::string& getTag() const { return tag; }

    void setVolume(float volume); // 個別の音量を設定
    float getVolume() const { return individualVolume; }

    void updateVolume(); // 実際の音量を更新

private:
    // コピーコンストラクタとコピー代入演算子の削除
    Sound(const Sound&) = delete;
    Sound& operator=(const Sound&) = delete;
};

} // namespace Sound
