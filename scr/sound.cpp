#include "../include/sound.hpp"
#include <SDL3/SDL_audio.h>

Sound::Sound(const std::string& path) {
    SDL_AudioSpec spec; 

    SDL_LoadWAV(path.c_str(), &spec, &m_buffer, &m_length);

    m_stream = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &spec, NULL, NULL);
}

Sound::Sound() {}

void Sound::play() {
    SDL_ClearAudioStream(m_stream);  

    SDL_PutAudioStreamData(m_stream, m_buffer, m_length);

    SDL_ResumeAudioStreamDevice(m_stream);
}

void Sound::stop() {
    SDL_PauseAudioStreamDevice(m_stream);

    SDL_ClearAudioStream(m_stream);
}

void Sound::pause() {
    SDL_PauseAudioStreamDevice(m_stream);
}

void Sound::resume() {
    SDL_ResumeAudioStreamDevice(m_stream);
}
