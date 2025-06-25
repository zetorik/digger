#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <algorithm>
#include <string>
#include "../include/player.hpp"
#include "../include/sprite_renderer.hpp"
#include "../include/texture_manager.hpp"
#include "../include/health_bar.hpp"

const int MAX_HEALTH = 100;
const Vec2 PLAYER_SIZE = Vec2(125, 125);
const std::string PLAYER_TEXTURE = "assets/miner.png";
const float SPEED = 20;
const float HITBOX_RADIUS = 50;
const float SPIN_TIME = 0.3;

Player::Player(SDL_Renderer* renderer, const Vec2& windowSize):
    ICollidable(&m_transform, HITBOX_RADIUS),
    m_windowSize(windowSize), 
    m_transform(windowSize / 2),
    m_spriteRenderer(renderer, &m_transform, PLAYER_SIZE, TextureManager::getInstance().getTexture(PLAYER_TEXTURE)), 
    m_health(MAX_HEALTH),
    m_healthBar(renderer, MAX_HEALTH, &m_health),
    m_inputManager(InputManager::getInstance()) {
        m_inputManager.registerDownCallback(SDL_SCANCODE_W, [this]() { onDownW(); });
        m_inputManager.registerDownCallback(SDL_SCANCODE_A, [this]() { onDownA(); });
        m_inputManager.registerDownCallback(SDL_SCANCODE_S, [this]() { onDownS(); });
        m_inputManager.registerDownCallback(SDL_SCANCODE_D, [this]() { onDownD(); });

        m_inputManager.registerUpCallback(SDL_SCANCODE_W, [this]() { onUpW(); });
        m_inputManager.registerUpCallback(SDL_SCANCODE_A, [this]() { onUpA(); });
        m_inputManager.registerUpCallback(SDL_SCANCODE_S, [this]() { onUpS(); });
        m_inputManager.registerUpCallback(SDL_SCANCODE_D, [this]() { onUpD(); });
    }

int Player::getHealth() const {
    return m_health;   
}

Vec2 Player::getPosition() const {
    return m_transform.position;
}

void Player::onDownW() {
    m_moveDirection += Vec2(0, -1);
}

void Player::onDownA() {
    m_moveDirection += Vec2(-1, 0);
}

void Player::onDownS() {
    m_moveDirection += Vec2(0, 1);
}

void Player::onDownD() {
    m_moveDirection += Vec2(1, 0);
}

void Player::onUpW() {
    m_moveDirection -= Vec2(0, -1);
}

void Player::onUpA() {
    m_moveDirection -= Vec2(-1, 0);
}

void Player::onUpS() {
    m_moveDirection -= Vec2(0, 1);
}

void Player::onUpD() {
    m_moveDirection -= Vec2(1, 0);
}

void Player::setHealth(int health) {
    m_health = std::clamp(health, 0, MAX_HEALTH);
}

void Player::takeDamage(int damage) {
    setHealth(m_health - damage);
}

void Player::heal(int health) {
    setHealth(m_health + health);
}

void Player::setPosition(const Vec2& pos) {
    m_transform.position = pos.clamped(Vec2(0, 0), m_windowSize - PLAYER_SIZE);
}

void Player::addFractals(int amount) {
    m_fractals += amount;
}

int Player::getFractals() const {
    return m_fractals;
}

void Player::spin() {
    m_isSpinning = true; 
}

void Player::update(float deltaTime) {
    if (m_health > 0) {
        setPosition(m_transform.position + m_moveDirection.normalized()*SPEED*(deltaTime*60));
    } else {
        m_transform.position += Vec2(0, 5 * (deltaTime*60));
    }


    if (m_isSpinning) {
        m_spriteRenderer.setAngle(m_spriteRenderer.getAngle() + 360*(deltaTime / SPIN_TIME));

        if (m_spriteRenderer.getAngle() == 0) {
            m_isSpinning = false;
        }
    }

    m_healthBar.update(deltaTime);
    m_spriteRenderer.render();
}
