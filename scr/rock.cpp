#include <SDL3/SDL_render.h>
#include <algorithm>
#include <random>
#include "../include/rock.hpp"
#include "../include/sprite_renderer.hpp"
#include "../include/collision_manager.hpp"
#include "../include/texture_manager.hpp"

const Vec2 MIN_SIZE = Vec2(56, 36);
const Vec2 MAX_SIZE = Vec2(127, 82.5);
const float GRAVITY = 0.025;
const float ACCELERATION = 0.025;
const Vec2 WINDOW_SIZE(640, 480);
const std::string ROCK_TEXTURE_PATH = "assets/rock.png";

Vec2 getRandomSize() {
    auto gen = globalRandomEngine();
    auto distX = std::uniform_real_distribution<float>(MIN_SIZE.x, MAX_SIZE.x);
    auto distY = std::uniform_real_distribution<float>(MIN_SIZE.y, MAX_SIZE.y);

    return Vec2(distX(gen), distY(gen));
}

Rock::Rock(SDL_Renderer* renderer, Vec2 startingPos, Vec2 direction, float velocity): 
    m_transform(startingPos),
    m_size(getRandomSize()),
    m_spriteRenderer(renderer, &m_transform, m_size, TextureManager::getInstance().getTexture(ROCK_TEXTURE_PATH)),
    m_velocity(velocity), 
    m_direction(direction) {

    tagCollidable = "Rock";
    m_collision = Collision(&m_transform, std::min<float>(m_size.x, m_size.y) * 0.45);
}

Rock::~Rock() {
    CollisionManager::getInstance().removeColliable(this);
}

void Rock::setPosition(const Vec2& pos) {
    m_transform.position = pos;
}

void Rock::update(float deltaTime) {
    setPosition(m_transform.position + m_direction*m_velocity*(deltaTime*60));

    if (
            m_transform.position.x < -m_size.x ||
            m_transform.position.y < -m_size.y ||
            m_transform.position.x > WINDOW_SIZE.x + m_size.x ||
            m_transform.position.y > WINDOW_SIZE.y + m_size.y
    ) {
        destroying = true;
        return;
    }


    m_direction.y -= GRAVITY*(deltaTime*60);
    m_direction = m_direction.normalized();

    m_velocity += ACCELERATION*(deltaTime*60);

    m_spriteRenderer.render();
}
