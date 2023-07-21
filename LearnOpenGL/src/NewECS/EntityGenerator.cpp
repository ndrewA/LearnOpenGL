#include "EntityGenerator.h"

Entity EntityGenerator::generateEntity()
{
    return freeIDs.empty() ? generateNewEntity() : reuseEntity();
}

Entity EntityGenerator::generateNewEntity()
{
    Entity entity{ entities.size() };
    entities.insert(entity);

    return Entity();
}

Entity EntityGenerator::reuseEntity()
{
    Entity entity{ freeIDs.front() };
    freeIDs.pop();
    entities.insert(entity);

    return Entity();
}

void EntityGenerator::freeEntity(Entity entity)
{
    entities.remove(entity);
    freeIDs.push(entity.id);
}