#pragma once

#include "SparseSet.h"

template <typename ComponentType>
class ComponentBuffer
{
public:
    void addComponent(Entity entity, ComponentType component)
    {
        entities.insert(entity);
        components[entities.getIndex(entity)] = std::move(component);
    }

    void removeComponent(Entity entity)
    {
        components.erase(entities.getIndex(entity));
        entities.remove(entity);
    }

    ComponentType& getComponent(Entity entity)
    {
        return components[entities.getIndex(entity)];
    }

    bool hasComponent(Entity entity) const
    {
        return entities.contains(entity);
    }

private:
    SparseSet entities;
    std::vector<ComponentType> components;
};
