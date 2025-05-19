#pragma once

#include <map>
#include <string>
#include <memory>
#include "Sound.h"

namespace Sound {

class SoundManager {
private:
    static SoundManager* instance;
    SoundManager();
    ~SoundManager();
    SoundManager(const SoundManager&) = delete;
    SoundManager& operator=(const SoundManager&) = delete;

    std::map<std::string, std::shared_ptr<Sound>> sounds;
    std::map<SoundType, float> typeVolumeScales;
    std::map<std::string, float> tagVolumeScales;

public:
    static SoundManager& getInstance();

    std::shared_ptr<Sound> loadSound(const std::string& filePath, SoundType type, const std::string& tag = "");
    void unloadSound(const std::string& filePath);

    void playSound(const std::string& filePath, bool loop = false);
    void stopSound(const std::string& filePath);
    void pauseSound(const std::string& filePath);
    void resumeSound(const std::string& filePath);

    void pauseSoundsWithTag(const std::string& tag);
    void resumeSoundsWithTag(const std::string& tag);
    void stopSoundsWithType(SoundType type);

    void stopAllSounds();
    void pauseAllSounds();
    void resumeAllSounds();

    // ボリューム設定
    void setVolumeScale(SoundType type, float scale);
    void setVolumeScaleForTag(const std::string& tag, float scale);
    float getVolumeScale(SoundType type, const std::string& tag) const;

private:
    std::shared_ptr<Sound> getSound(const std::string& filePath) const;
    void updateAllSoundVolumes(); // 全サウンドのボリュームを再計算
};

} // namespace Sound
