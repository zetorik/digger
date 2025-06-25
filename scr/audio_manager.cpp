#include "../include/audio_manager.hpp"
#include <SDL3/SDL_audio.h>
#include <string>
#include "../include/sound.hpp"

AudioManager::AudioManager() {}

AudioManager& AudioManager::getInstance() {
    static AudioManager instance;
    return instance;
}

Sound* AudioManager::getSound(const std::string& path) {
    auto it = m_sounds.find(path);
    if (it != m_sounds.end()) {
        return it->second.get();
    }

    std::unique_ptr<Sound> sound = std::make_unique<Sound>(path);
    Sound* p = sound.get();

    m_sounds[path] = std::move(sound);

    return p;
}

