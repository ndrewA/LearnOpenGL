#pragma once

#include <stdexcept>

#include "SparseSet.h"

template <typename ComponentType>
class ComponentBuffer
{
public:
    void addComponent(Entity entity, ComponentType&& component)
    {
        if (entities.contains(entity.id))
            throw std::runtime_error("Entity already owns component!");

        entities.insert(entity.id);

        size_t entityIndex = entities.getIndex(entity.id);

        if (entityIndex >= components.size())
            components.resize(entityIndex + 10);

        components[entityIndex] = std::move(component);
    }

    void removeComponent(Entity entity)
    {
        if (entities.contains(entity.id) == false)
            return;

        components.erase(components.begin() + entities.getIndex(entity.id));
        entities.remove(entity.id);
    }

    ComponentType& getComponent(Entity entity)
    {
        return components[entities.getIndex(entity.id)];
    }

    bool hasComponent(Entity entity) const
    {
        return entities.contains(entity.id);
    }

private:
    SparseSet<EntityID> entities;
    std::vector<ComponentType> components;
};
