#pragma once

#include "ComponentRemover.h"

template <typename... ComponentTypes>
class ComponentManager
{
public:
    ComponentManager()
        : componentRemover(componentBuffers)
    {
    }

    template <typename... EntityComponentTypes>
    void addToEntity(Entity entity, EntityComponentTypes&&... components)
    {
        (std::get<ComponentBuffer<EntityComponentTypes>>(componentBuffers)
            .addComponent(entity, std::forward<EntityComponentTypes>(components)), ...);
    }

    template <typename ComponentType>
    void removeFromEntity(Entity entity)
    {
        std::get<ComponentBuffer<ComponentType>>(componentBuffers).removeComponent(entity);
    }

    void removeEntity(Entity entity, const std::vector<size_t>& componentIndices)
    {
        for (size_t index : componentIndices)
            componentRemover.removeComponent(entity, index);
    }

    template <typename ComponentType>
    ComponentType& getComponent(Entity entity)
    {
        return std::get<ComponentBuffer<ComponentType>>(componentBuffers).getComponent(entity);
    }

    template <typename ComponentType>
    bool hasComponent(Entity entity) const
    {
        return std::get<ComponentBuffer<ComponentType>>(componentBuffers).hasComponent(entity);
    }

private:
    std::tuple<ComponentBuffer<ComponentTypes>...> componentBuffers;
    ComponentRemover<ComponentTypes...> componentRemover;
};