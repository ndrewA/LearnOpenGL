#include "EntityManager.h"

std::weak_ptr<Entity> EntityManager::createEntity()
{
    auto entity = std::make_shared<Entity>(entities.size());
    entities.push_back(entity);
    return entity;
}

void EntityManager::removeEntity(Entity entity)
{
    if (entity.index >= entities.size() || entities.empty())
        throw EntityOutOfBoundsException(entity);

    if (entity.index < entities.size()) {   
        entities[entity.index] = entities.back();
        entities[entity.index]->index = entity.index;
    }

    entities.pop_back();
}
