#pragma once

#include "icollidable.hpp"
#include "itransformable.hpp"
#include "iupdatable.hpp"
#include "sprite_renderer.hpp"
#include "transform.hpp"
#include "utils.hpp"
#include <SDL3/SDL_render.h>

class Rock : public IUpdatable, public ITrasformable, public ICollidable {
    public:
        Rock(SDL_Renderer* renderer, Vec2 startingPos, Vec2 direction, float velocity);
        ~Rock();
        void setPosition(const Vec2& pos);
        void update(float deltaTime) override;
    private:
        Transform m_transform;
        Vec2 m_size;
        Vec2 m_direction;
        float m_velocity;
        SpriteRenderer m_spriteRenderer;
};
