#pragma once

#include "transform.hpp"

class Collision {
    public:
        Collision(Transform* transform, float radius);
        Vec2 getPosition() const;
        float getRadius() const;
    private:
        Transform* m_transform;
        float m_radius;
};
