#pragma once

#include "itransformable.hpp"
#include "iupdatable.hpp"
#include "sprite_renderer.hpp"
#include <SDL3/SDL_render.h>

class Explosion : public IUpdatable, public ITrasformable {
    public:
        Explosion(SDL_Renderer* renderer, const Vec2& pos);
        void update(float deltaTime) override;
    private:
        void showNextSprite();
        SpriteRenderer m_spriteRenderer;
        Transform m_transform;
        float m_timePerSprite;
        float m_spriteTimer;
        Uint8 m_spriteIndex;
};
