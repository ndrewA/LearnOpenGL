#pragma once

#include <unordered_set>
#include <stdexcept>

#include "Entity.h"

class EntityLifecycleManager
{
public:
    using EntitySet = std::unordered_set<Entity>;

    Entity createEntity();
    bool destroyEntity(const Entity entity);

    const EntitySet& getActiveEntities() const { return activeEntities; }

private:
    EntitySet freeEntities;
    EntitySet activeEntities;
    Entity nextEntity = 0;
};
