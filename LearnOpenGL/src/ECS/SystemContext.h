#pragma once

#include "EntityQueryManager.h"

class SystemContext
{
public:
    SystemContext(EntityLifecycleManager& lifecycleManager, ComponentManager& componentManager)
        : entityQuery(lifecycleManager, componentManager), 
          componentManager(componentManager) 
    { 
    }

    template<typename ComponentType>
    requires std::derived_from<ComponentType, Component>
    const ComponentType& getComponent(const Entity entity)
    {
        return componentManager.getComponent<ComponentType>(entity);
    }

    template<typename ComponentType>
    requires std::derived_from<ComponentType, Component>
    bool hasComponent(const Entity entity)
    {
        return componentManager.hasComponent<ComponentType>(entity);
    }

    template<typename... ComponentTypes>
    requires (std::derived_from<ComponentTypes, Component> && ...)
    std::vector<Entity> getEntitiesWithComponents()
    {
        return entityQuery.getEntitiesWithComponents<ComponentTypes...>();
    }

private:
    EntityQueryManager entityQuery;
    ComponentManager& componentManager;
};