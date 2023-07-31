#include "EntityGenerator.h"

Entity EntityGenerator::generateEntity()
{
    return freeIDs.empty() ? generateNewEntity() : reuseEntity();
}

Entity EntityGenerator::generateNewEntity()
{
    Entity entity{ entities.size() };
    entities.insert(entity.id);

    return Entity();
}

Entity EntityGenerator::reuseEntity()
{
    Entity entity{ freeIDs.front() };
    freeIDs.pop();
    entities.insert(entity.id);

    return Entity();
}

void EntityGenerator::freeEntity(Entity entity)
{
    entities.remove(entity.id);
    freeIDs.push(entity.id);
}