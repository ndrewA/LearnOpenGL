#pragma once

#include <memory>
#include <vector>

#include "EntityExceptions.h"

class EntityManager
{
public:
    std::weak_ptr<Entity> createEntity();
    void removeEntity(Entity entity);

    size_t getEntityCount() const { return entities.size(); }

private:
    std::vector<std::shared_ptr<Entity>> entities;
};
