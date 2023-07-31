#pragma once

#include "ComponentBuffer.h"

template <typename... ComponentTypes>
class ComponentManager
{
public:
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

    void removeEntity(Entity entity)
    {
        (std::get<ComponentBuffer<ComponentTypes>>(componentBuffers).removeComponent(entity), ...);
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
};