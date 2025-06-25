#pragma once

#include <SDL3/SDL_audio.h>
#include <SDL3/SDL_stdinc.h>
#include <string>

class Sound {
    public:
        Sound(const std::string& path);
        Sound();
        void play();
        void stop();
        void resume();
        void pause();
    private:
        Uint32 m_length;
        Uint8* m_buffer;
        SDL_AudioStream* m_stream;
};
