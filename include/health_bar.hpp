#pragma once

#include "itransformable.hpp"
#include "iupdatable.hpp"
#include "sprite_renderer.hpp"

class HealthBar : public IUpdatable, public ITrasformable {
    public:
        HealthBar(SDL_Renderer* renderer, int maxHealth, const int* health);
        void update(float deltaTime) override;
    private:
        Transform m_transform;
        int m_maxHealth;
        SDL_FRect m_rect;
        SDL_Renderer* m_renderer;
        const int* m_health;
};
