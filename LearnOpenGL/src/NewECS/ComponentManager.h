#pragma once

#include "ComponentStorage.h"
#include "EntityMetadata.h"

template <typename... ComponentTypes>
class ComponentManager
{
public:
    template<typename... ComponentTypes>
    void addToEntity(Entity entity, ComponentTypes... components)
    {
        componentStorage.addToEntity(entity, components...);
        entityMetadata.addToEntity(entity, components...);
    }

    void removeEntity(Entity entity)
    {
        componentStorage.removeEntity(entity);
        entityMetadata.removeEntity(entity);
    }

    template <typename ComponentType>
    ComponentType& getComponent(Entity entity)
    {
        return componentStorage.getComponent<ComponentType>(entity);
    }

    template <typename ComponentType>
    bool hasComponent(Entity entity) const
    {
        return entityMetadata.hasComponent<ComponentType>(entity);
    }

private:
    ComponentStorage<ComponentTypes...> componentStorage;
    EntityMetadata entityMetadata;
};