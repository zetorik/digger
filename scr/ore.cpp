#include "../include/ore.hpp"
#include "../include/collision_manager.hpp"
#include "../include/texture_manager.hpp"
#include <string>

const Vec2 SIZE(75, 75);
const float HITBOX_RADIUS = 40; 
const std::string URANIUM_TEXTURE_PATH = "assets/uranium.png";
const std::string IRON_TEXTURE_PATH = "assets/iron.png";
const std::string COBALT_TEXTURE_PATH = "assets/cobalt.png";
const float fadeInTime = 2.5;

Ore::Ore(SDL_Renderer* renderer, const Vec2& pos, OreType type):
    m_transform(pos) {

    m_collision = Collision(&m_transform, HITBOX_RADIUS);
    tagCollidable = "Ore";

    std::string path;

    switch (type) {
        case OreType::Uranium:
            m_price = 9;
            path = URANIUM_TEXTURE_PATH;
            break;
        case OreType::Iron:
            m_price = 3;
            path = IRON_TEXTURE_PATH;
            break;
        case OreType::Cobalt:
            m_price = 6;
            path = COBALT_TEXTURE_PATH;
            break;
    }

    m_spriteRenderer = SpriteRenderer(renderer, &m_transform, SIZE, TextureManager::getInstance().getTexture(path));
    m_spriteRenderer.setAlpha(0);
}

Ore::~Ore() {
    CollisionManager::getInstance().removeColliable(this);
}

int Ore::getPrice() const {
    return m_price;
}

void Ore::update(float deltaTime) {
    float alpha = m_spriteRenderer.getAlpha();

    if (alpha != 1) {
        m_spriteRenderer.setAlpha(alpha + deltaTime / fadeInTime);
    }

    m_spriteRenderer.render();
}
