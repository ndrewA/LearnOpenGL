#pragma once

#include "ComponentManager.h"
#include "EntityLifecycleManager.h"

class EntityQueryManager
{
public:
    EntityQueryManager(EntityLifecycleManager& lifecycleManager, ComponentManager& componentManager)
        : lifecycleManager(lifecycleManager), componentManager(componentManager) {}

    template<typename... ComponentTypes>
    requires (std::derived_from<ComponentTypes, Component> && ...)
    std::vector<Entity> getEntitiesWithComponents()
    {
        std::vector<Entity> entities;

        const auto& activeEntites = lifecycleManager.getActiveEntities();
        for (const auto& entity : activeEntites)
            if ((componentManager.hasComponent<ComponentTypes>(entity) && ...))
                entities.push_back(entity);

        return entities;
    }

private:
    ComponentManager& componentManager;
    EntityLifecycleManager& lifecycleManager;
};