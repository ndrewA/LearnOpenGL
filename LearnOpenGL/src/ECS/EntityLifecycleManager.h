#pragma once

#include <unordered_set>
#include <stdexcept>

#include "Entity.h"

class EntityLifecycleManager
{
public:
    Entity createEntity();
    void destroyEntity(const Entity entity);

    const std::unordered_set<Entity>& getActiveEntities() const { return activeEntities; }

private:
    std::unordered_set<Entity> freeEntities;
    std::unordered_set<Entity> activeEntities;
    Entity nextEntity = 0;
};
