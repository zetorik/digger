#include "../include/texture_manager.hpp"
#include <SDL3/SDL_render.h>
#include <SDL3_image/SDL_image.h>

TextureManager::TextureManager() {}

TextureManager& TextureManager::getInstance() {
     static TextureManager instance;
     return instance;
}

void TextureManager::setRenderer(SDL_Renderer* renderer) {
    m_renderer = renderer;
}

SDL_Texture* TextureManager::getTexture(const std::string& path) {
    auto it = m_textures.find(path);
    
    if (it != m_textures.end()) {
        return it->second;
    }

    SDL_Texture* texture = IMG_LoadTexture(m_renderer, path.c_str());

    m_textures[path] = texture;

    return texture;
}
