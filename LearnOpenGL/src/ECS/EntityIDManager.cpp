#include "EntityIDManager.h"

#include "EntityExceptions.h"

Entity EntityIDManager::createEntity()
{
    Entity entity;

    if (!freeEntities.empty()) {
        entity = freeEntities.front();
        freeEntities.pop();
    }
    else {
        entity = nextEntity++;
    }

    activeEntities.insert(entity);
    return entity;
}

void EntityIDManager::destroyEntity(Entity entity)
{
    if (activeEntities.find(entity) == activeEntities.end())
        throw EntityOutOfBoundsException(entity);

    freeEntities.push(entity);
    activeEntities.erase(entity);
}
