#pragma once

#include <SDL3/SDL.h>
#include "health_bar.hpp"
#include "icollidable.hpp"
#include "input_manager.hpp"
#include "itransformable.hpp"
#include "sprite_renderer.hpp"
#include "utils.hpp"
#include "iupdatable.hpp"

class Player : public IUpdatable, public ICollidable, public ITrasformable  {
    public:
        Player(SDL_Renderer* renderer, const Vec2& windowSize);
        int getHealth() const;
        void takeDamage(int damage);
        void heal(int health);
        void setPosition(const Vec2& position);
        Vec2 getPosition() const;
        void update(float deltaTime) override;
        void addFractals(int amount);
        int getFractals() const;
        void spin();
    private:
        void onDownW();
        void onDownA();
        void onDownS();
        void onDownD();
        void onUpW();
        void onUpA();
        void onUpS();
        void onUpD();
        void setHealth(int health);

        const Vec2 m_windowSize;
        SpriteRenderer m_spriteRenderer;
        Transform m_transform;
        InputManager& m_inputManager;
        int m_health;
        Vec2 m_moveDirection;
        int m_fractals = 0;
        bool m_isSpinning = false;
        HealthBar m_healthBar;
};

