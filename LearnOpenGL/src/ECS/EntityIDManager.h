#pragma once

#include <queue>
#include <unordered_set>

#include "Entity.h"

class EntityIDManager
{
public:
    Entity createEntity();
    void destroyEntity(Entity entity);

    const std::unordered_set<Entity>& getActiveEntities() const { return activeEntities; }

private:
    std::queue<Entity> freeEntities;
    std::unordered_set<Entity> activeEntities;
    Entity nextEntity = 0;
};
