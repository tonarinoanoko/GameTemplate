#include "SoundManager.h"
#include "System/Log/Logger.h"

namespace Sound {

SoundManager* SoundManager::instance = nullptr;

SoundManager::SoundManager() {
    // デフォルトのボリュームスケールを設定
    typeVolumeScales[SoundType::BGM] = 1.0f;
    typeVolumeScales[SoundType::SE] = 1.0f;
    LOGGER_INFO("SoundManager initialized.");
}

SoundManager::~SoundManager() {
    stopAllSounds();
    sounds.clear();
    LOGGER_INFO("SoundManager finalized.");
}

SoundManager& SoundManager::getInstance() {
    if (!instance) {
        instance = new SoundManager();
    }
    return *instance;
}

std::shared_ptr<Sound> SoundManager::loadSound(const std::string& filePath, SoundType type, const std::string& tag) {
    auto it = sounds.find(filePath);
    if (it == sounds.end()) {
        auto newSound = std::make_shared<Sound>(filePath, type, tag);
        if (newSound->load()) {
            sounds[filePath] = newSound;
            return newSound;
        }
        return nullptr;
    } else {
        LOGGER_WARNING("Sound already loaded: %s", filePath.c_str());
        return it->second;
    }
}

void SoundManager::unloadSound(const std::string& filePath) {
    auto it = sounds.find(filePath);
    if (it != sounds.end()) {
        sounds.erase(it);
        LOGGER_DEBUG("Sound unloaded from manager: %s", filePath.c_str());
    } else {
        LOGGER_WARNING("Sound not found in manager: %s", filePath.c_str());
    }
}

void SoundManager::playSound(const std::string& filePath, bool loop) {
    auto sound = getSound(filePath);
    if (sound) {
        sound->play(loop);
    }
}

void SoundManager::stopSound(const std::string& filePath) {
    auto sound = getSound(filePath);
    if (sound) {
        sound->stop();
    }
}

void SoundManager::pauseSound(const std::string& filePath) {
    auto sound = getSound(filePath);
    if (sound) {
        sound->pause();
    }
}

void SoundManager::resumeSound(const std::string& filePath) {
    auto sound = getSound(filePath);
    if (sound) {
        sound->resume();
    }
}

void SoundManager::pauseSoundsWithTag(const std::string& tag) {
    for (const auto& pair : sounds) {
        if (pair.second->getTag() == tag) {
            pair.second->pause();
        }
    }
    LOGGER_DEBUG("Sounds with tag '%s' paused.", tag.c_str());
}

void SoundManager::resumeSoundsWithTag(const std::string& tag) {
    for (const auto& pair : sounds) {
        if (pair.second->getTag() == tag) {
            pair.second->resume();
        }
    }
    LOGGER_DEBUG("Sounds with tag '%s' resumed.", tag.c_str());
}

void SoundManager::stopSoundsWithType(SoundType type) {
    for (const auto& pair : sounds) {
        if (pair.second->getType() == type) {
            pair.second->stop();
        }
    }
    LOGGER_DEBUG("Sounds with type %d stopped.", static_cast<int>(type));
}

void SoundManager::stopAllSounds() {
    for (const auto& pair : sounds) {
        pair.second->stop();
    }
    LOGGER_DEBUG("All sounds stopped.");
}

void SoundManager::pauseAllSounds() {
    for (const auto& pair : sounds) {
        pair.second->pause();
    }
    LOGGER_DEBUG("All sounds paused.");
}

void SoundManager::resumeAllSounds() {
    for (const auto& pair : sounds) {
        pair.second->resume();
    }
    LOGGER_DEBUG("All sounds resumed.");
}

void SoundManager::setVolumeScale(SoundType type, float scale) {
    typeVolumeScales[type] = std::max(0.0f, std::min(1.0f, scale));
    updateAllSoundVolumes();
    LOGGER_INFO("Volume scale set for type %d: %.2f", static_cast<int>(type), typeVolumeScales[type]);
}

void SoundManager::setVolumeScaleForTag(const std::string& tag, float scale) {
    tagVolumeScales[tag] = std::max(0.0f, std::min(1.0f, scale));
    updateAllSoundVolumes();
    LOGGER_INFO("Volume scale set for tag '%s': %.2f", tag.c_str(), tagVolumeScales[tag]);
}

float SoundManager::getVolumeScale(SoundType type, const std::string& tag) const {
    float finalScale = 1.0f;
    if (typeVolumeScales.count(type)) {
        finalScale *= typeVolumeScales.at(type);
    }
    if (tagVolumeScales.count(tag)) {
        finalScale *= tagVolumeScales.at(tag);
    }
    return finalScale;
}

std::shared_ptr<Sound> SoundManager::getSound(const std::string& filePath) const {
    auto it = sounds.find(filePath);
    if (it != sounds.end()) {
        return it->second;
    }
    LOGGER_ERROR("Sound not found in manager: %s", filePath.c_str());
    return nullptr;
}

void SoundManager::updateAllSoundVolumes() {
    for (const auto& pair : sounds) {
        pair.second->updateVolume();
    }
}

} // namespace Sound
