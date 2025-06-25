#include "../include/explosion.hpp"
#include "../include/texture_manager.hpp"
#include <SDL3/SDL_render.h>

const Vec2 EXPLOSION_SIZE(100, 100);
const float DURATION = 0.7;
const Vec2 TEXTURE_SIZE(256, 256);
const Vec2 SOURCE_SIZE(64, 64);
const Uint8 SPRITE_AMOUNT = 16;
const Uint8 ROW_AMOUNT = 4;
const std::string EXPLOSION_TEXTURE_PATH = "assets/exp.png";

Explosion::Explosion(SDL_Renderer* renderer, const Vec2& pos):
    m_transform(pos),
    m_spriteRenderer(renderer, &m_transform, EXPLOSION_SIZE, TextureManager::getInstance().getTexture(EXPLOSION_TEXTURE_PATH)),
    m_timePerSprite(DURATION / SPRITE_AMOUNT),
    m_spriteTimer(0),
    m_spriteIndex(0) {

    m_spriteRenderer.setSourceSize(SOURCE_SIZE);
    m_spriteRenderer.setSourcePosition(SOURCE_SIZE * 3);
}

void Explosion::showNextSprite() {
    m_spriteIndex += 1;    

    float row = static_cast<float>((ROW_AMOUNT-1) - m_spriteIndex / ROW_AMOUNT);
    Vec2 p = Vec2(
                //                                              wrong but looks cool
                SOURCE_SIZE.x * ((ROW_AMOUNT-1) - m_spriteIndex % (ROW_AMOUNT-1)), 
                SOURCE_SIZE.y * row);

    m_spriteRenderer.setSourcePosition(p);

   // std::cout << p << row << std::endl; 
}

void Explosion::update(float deltaTime) {
    m_spriteTimer += deltaTime;

    if (m_spriteTimer >= m_timePerSprite) {
        if (m_spriteIndex >= SPRITE_AMOUNT) {
            destroying = true;
            return;
        }

        showNextSprite();
        
        m_spriteTimer -= m_timePerSprite;
    }

    m_spriteRenderer.render();
}
