#include "EntityLifecycleManager.h"

Entity EntityLifecycleManager::createEntity()
{
    Entity entity;

    if (!freeEntities.empty()) {
        entity = *freeEntities.begin();
        freeEntities.erase(entity);
    }
    else {
        entity = nextEntity++;
    }

    activeEntities.insert(entity);
    return entity;
}

bool EntityLifecycleManager::destroyEntity(const Entity entity)
{
    if (activeEntities.find(entity) == activeEntities.end())
        throw std::runtime_error("Entity out of bounds!");

    freeEntities.insert(entity);
    if (entity == nextEntity) {
        auto it = freeEntities.find(nextEntity);
        while (it != freeEntities.end()) {
            freeEntities.erase(it);
            --nextEntity;
            it = freeEntities.find(nextEntity);
        }
    }

    activeEntities.erase(entity);
}
