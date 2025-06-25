#include <SDL3/SDL_render.h>
#include <SDL3/SDL_surface.h>
#include <SDL3_image/SDL_image.h>
#include <algorithm>
#include "../include/sprite_renderer.hpp"

void SpriteRenderer::setTexture(SDL_Texture* texture) {
    m_texture = texture;
}

void SpriteRenderer::setSize(const Vec2& size) {
    m_rect.w = size.x;
    m_rect.h = size.y;
}

void SpriteRenderer::updatePosition() {
    m_rect.x = m_transform->position.x;
    m_rect.y = m_transform->position.y;
}

void SpriteRenderer::setSourcePosition(const Vec2& pos) {
    m_sourceRect.x = pos.x;
    m_sourceRect.y = pos.y;
}

void SpriteRenderer::setSourceSize(const Vec2& size) {
    m_sourceRect.w = size.x;
    m_sourceRect.h = size.y;
}

void SpriteRenderer::setAlpha(float alpha) {
    m_alpha = std::clamp<float>(alpha, 0, 1);
}

void SpriteRenderer::setAngle(double angle) {
    if (angle >= 360) {
        m_angle = 0;
        return;
    }

    m_angle = std::clamp<double>(angle, 0, 360);
}

float SpriteRenderer::getAlpha() const {
    return m_alpha;
}

double SpriteRenderer::getAngle() const {
    return m_angle;
}

SpriteRenderer::SpriteRenderer(
        SDL_Renderer* renderer,
        Transform* transform, 
        const Vec2& size, 
        SDL_Texture* texture 
):
    m_renderer(renderer),
    m_transform(transform), 
    m_texture(texture) {
    m_rect = {
        transform->position.x, 
        transform->position.y,
        size.x,
        size.y,
    };

    float texWidth, texHeight;
    SDL_GetTextureSize(texture, &texWidth, &texHeight);

    m_sourceRect = {
        0,
        0,
        texWidth, 
        texHeight,
    };
}

SpriteRenderer::SpriteRenderer() {}

void SpriteRenderer::render() {
    updatePosition();    

    SDL_SetTextureAlphaModFloat(m_texture, m_alpha);

    SDL_RenderTextureRotated(m_renderer, m_texture, &m_sourceRect, &m_rect, m_angle, NULL, SDL_FLIP_NONE);
    
    SDL_SetTextureAlphaModFloat(m_texture, 1);
}
