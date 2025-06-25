#pragma once

#include <SDL3/SDL.h>
#include <SDL3/SDL_render.h>
#include "transform.hpp"
#include "utils.hpp"

class SpriteRenderer {
    public:
        SpriteRenderer(SDL_Renderer* renderer, Transform* transform, const Vec2& size, SDL_Texture* texture);
        SpriteRenderer();
        void render();
        void setSize(const Vec2& size);
        void setSourcePosition(const Vec2& pos);
        void setSourceSize(const Vec2& size);
        void setTexture(SDL_Texture* texture);
        void setAlpha(float alpha);
        void setAngle(double angle);
        float getAlpha() const;
        double getAngle() const;
    private:
        void updatePosition();
        SDL_Renderer* m_renderer;
        SDL_Texture* m_texture;
        SDL_FRect m_rect;
        SDL_FRect m_sourceRect;
        Transform* m_transform;
        float m_alpha = 1;
        double m_angle = 0;
};
