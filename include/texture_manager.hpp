#pragma once

#include <SDL3/SDL_render.h>
#include <string>
#include <unordered_map>

class TextureManager {
    public:
        static TextureManager& getInstance();
        SDL_Texture* getTexture(const std::string& path);
        void setRenderer(SDL_Renderer* renderer);
    private:
        TextureManager();
        std::unordered_map<std::string, SDL_Texture*> m_textures;
        SDL_Renderer* m_renderer;
};
