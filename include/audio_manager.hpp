#pragma once

#include <SDL3/SDL_audio.h>
#include <memory>
#include <unordered_map>
#include <string>
#include "sound.hpp"

class AudioManager {
    public:
        static AudioManager& getInstance();
        Sound* getSound(const std::string& path);
    private:
        AudioManager();
        std::unordered_map<std::string, std::unique_ptr<Sound>> m_sounds;
};
