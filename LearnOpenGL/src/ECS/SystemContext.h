#pragma once

#include "ComponentManager.h"
#include "EntityIDManager.h"

class SystemContext
{
public:
    SystemContext(EntityIDManager& IDManager, ComponentManager& componentManager)
        : IDManager(IDManager), componentManager(componentManager)  { }

    template<typename ComponentType>
    requires std::derived_from<ComponentType, Component>
    const ComponentType& getComponent(Entity entity)
    {
        return componentManager.getComponent<ComponentType>(entity);
    }

    template<typename ComponentType>
    requires std::derived_from<ComponentType, Component>
    bool hasComponent(Entity entity)
    {
        return componentManager.hasComponent<ComponentType>(entity);
    }

    template<typename... ComponentTypes>
    requires (std::derived_from<ComponentTypes, Component> && ...)
    std::vector<Entity> getEntitiesWithComponents()
    {
        std::vector<Entity> entities;

        auto& activeEntites = IDManager.getActiveEntities();
        for (const auto& entity : activeEntites)
            if ((componentManager.hasComponent<ComponentTypes>(entity) && ...))
                entities.push_back(entity);

        return entities;
    }

private:
    EntityIDManager& IDManager;
    ComponentManager& componentManager;
};