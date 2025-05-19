#include "Sound.h"
#include <algorithm>
#include <DxLib.h>
#include "System/Log/Logger.h"
#include "SoundManager.h"

namespace Sound {

Sound::Sound(const std::string& path, SoundType soundType, const std::string& soundTag)
    : filePath(path), type(soundType), tag(soundTag) {}

Sound::~Sound() {
    if (soundHandle != -1) {
        StopSoundMem(soundHandle);
        DeleteSoundMem(soundHandle);
        LOGGER_DEBUG("Sound unloaded: %s", filePath.c_str());
        soundHandle = -1;
    }
}

bool Sound::load() {
    if (soundHandle == -1) {
        soundHandle = LoadSoundMem(filePath.c_str());
        if (soundHandle == -1) {
            LOGGER_ERROR("Failed to load sound: %s", filePath.c_str());
            return false;
        }
        LOGGER_DEBUG("Sound loaded: %s, Handle: %d, Type: %d, Tag: %s", filePath.c_str(), soundHandle, static_cast<int>(type), tag.c_str());
        updateVolume(); // ロード時に初期音量を設定
        return true;
    } else {
        LOGGER_WARNING("Sound already loaded: %s", filePath.c_str());
        return true;
    }
}

void Sound::play(bool loop) {
    if (soundHandle != -1) {
        PlaySoundMem(soundHandle, DX_PLAYTYPE_BACK);
        if (loop && type == SoundType::BGM) {
            ChangeCurrentStream(soundHandle);
            SetLoopStream(soundHandle, DX_LOOPSTREAM_NORMAL);
        }
        LOGGER_DEBUG("Sound played: %s, Loop: %s, Volume: %.2f", filePath.c_str(), loop ? "true" : "false", individualVolume);
    } else {
        LOGGER_ERROR("Sound not loaded: %s", filePath.c_str());
    }
}

void Sound::stop() {
    if (soundHandle != -1) {
        StopSoundMem(soundHandle);
        LOGGER_DEBUG("Sound stopped: %s", filePath.c_str());
    } else {
        LOGGER_ERROR("Sound not loaded: %s", filePath.c_str());
    }
}

void Sound::pause() {
    if (soundHandle != -1) {
        PauseSoundMem(soundHandle);
        LOGGER_DEBUG("Sound paused: %s", filePath.c_str());
    } else {
        LOGGER_ERROR("Sound not loaded: %s", filePath.c_str());
    }
}

void Sound::resume() {
    if (soundHandle != -1) {
        ResumeSoundMem(soundHandle);
        LOGGER_DEBUG("Sound resumed: %s", filePath.c_str());
    } else {
        LOGGER_ERROR("Sound not loaded: %s", filePath.c_str());
    }
}

void Sound::setVolume(float volume) {
    individualVolume = std::clamp(volume, 0.0f, 1.0f);
    updateVolume();
    LOGGER_DEBUG("Individual volume set for %s: %.2f", filePath.c_str(), individualVolume);
}

void Sound::updateVolume() {
    if (soundHandle != -1) {
        float finalVolume = individualVolume * SoundManager::getInstance().getVolumeScale(type, tag);
        SetVolumeSoundMem(soundHandle, static_cast<int>(finalVolume * 255)); // DxLib のボリュームは 0 ~ 255
    }
}

} // namespace Sound
