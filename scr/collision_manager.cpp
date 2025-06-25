#include "../include/collision_manager.hpp"
#include <vector>

CollisionManager::CollisionManager() {}

CollisionManager& CollisionManager::getInstance() {
    static CollisionManager instance;
    return instance;
}

void CollisionManager::addCollidable(ICollidable* collidable) {
    m_collidables.insert(collidable);
}

void CollisionManager::removeColliable(ICollidable* collidable) {
    m_collidables.erase(collidable);
}

std::vector<ICollidable*> CollisionManager::getCollisions(ICollidable* collidable) {
    const Collision& collision = collidable->getCollision();
    Vec2 pos = collision.getPosition();
    float radius = collision.getRadius();

    std::vector<ICollidable*> collidables;
    
    for (ICollidable* otherCollidable : m_collidables) {
        if (collidable == otherCollidable) {
            continue; 
        }

        const Collision& otherCollision = otherCollidable->getCollision();
        
        if (circlesIntersect(
                    pos, 
                    radius,
                    otherCollision.getPosition(),
                    otherCollision.getRadius())
         ) {
            collidables.push_back(otherCollidable);
        }
    }

    return collidables;
}
