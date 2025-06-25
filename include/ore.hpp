#pragma once

#include "icollidable.hpp"
#include "itransformable.hpp"
#include "iupdatable.hpp"
#include "sprite_renderer.hpp"
#include "transform.hpp"
#include <SDL3/SDL_render.h>

enum class OreType {
    Uranium,
    Iron,
    Cobalt
};

class Ore : public IUpdatable, public ITrasformable, public ICollidable {
    public:
        Ore(SDL_Renderer* renderer, const Vec2& pos, OreType type);
        ~Ore();
        void update(float deltaTime) override;
        int getPrice() const;
    private:
        Transform m_transform;
        SpriteRenderer m_spriteRenderer;
        int m_price;
};
