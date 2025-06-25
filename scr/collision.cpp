#include "../include/collision.hpp"

Collision::Collision(Transform* transform, float radius): 
    m_transform(transform), 
    m_radius(radius) {
    }

float Collision::getRadius() const { return m_radius; };
Vec2 Collision::getPosition() const { return m_transform->position; };
