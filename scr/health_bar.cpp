#include "../include/health_bar.hpp"
#include <SDL3/SDL_render.h>

const Vec2 BAR_POS(485, 5);
const Vec2 BAR_SIZE(150, 25);

HealthBar::HealthBar(SDL_Renderer* renderer, int maxHealth, const int* health):
    m_health(health),
    m_renderer(renderer),
    m_transform(BAR_POS),
    m_maxHealth(maxHealth),
    m_rect({BAR_POS.x, BAR_POS.y, BAR_SIZE.x, BAR_SIZE.y}) {}

void HealthBar::update(float deltaTime) {
    m_rect.w = (static_cast<float>(*m_health) / m_maxHealth) * BAR_SIZE.x;

    SDL_SetRenderDrawColor(m_renderer, 90, 207, 135, 1);
    SDL_RenderFillRect(m_renderer, &m_rect);
}
