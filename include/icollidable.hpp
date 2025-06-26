#pragma once

#include "collision.hpp"
#include "transform.hpp"
#include <string>

class ICollidable {
    public:
        const Collision& getCollision() { return m_collision; } ;
        ICollidable(Transform* transform, float radius) : m_collision(transform, radius) {

        }
        ICollidable() {};
        std::string tagCollidable = "Object";
    protected:
        Collision m_collision;
};
