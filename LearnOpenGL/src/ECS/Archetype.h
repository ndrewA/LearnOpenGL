#pragma once

#include <unordered_set>

#include "Entity.h"
#include "SparseSet.h"

class Archetype 
{
public:
    void addEntity(Entity entity) { entities.insert(entity.index, entity); }
    void removeEntity(Entity entity) { entities.remove(entity.index); }
    bool hasEntity(Entity entity) const { return entities.has(entity.index); }
    const std::vector<Entity>& getEntities() const { return entities.getAll(); }

private:
    SparseSet<Entity> entities;
};