#include "EntityLifecycleManager.h"

#include "EntityExceptions.h"

Entity EntityLifecycleManager::createEntity()
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

void EntityLifecycleManager::destroyEntity(const Entity entity)
{
    if (activeEntities.find(entity) == activeEntities.end())
        throw EntityOutOfBoundsException(entity);

    freeEntities.push(entity);
    activeEntities.erase(entity);
}
