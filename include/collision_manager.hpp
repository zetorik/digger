#pragma once

#include "icollidable.hpp"
#include <unordered_set>
#include <vector>

class CollisionManager {
    public:
        static CollisionManager& getInstance();
        void addCollidable(ICollidable* collidable);
        void removeColliable(ICollidable* collidable);
        std::vector<ICollidable*> getCollisions(ICollidable* collidable);
    private:
        CollisionManager();
        std::unordered_set<ICollidable*> m_collidables;
};
