#pragma once

#include "ComponentIndices.h"
#include "SparseSet.h"

template<typename... ComponentTypes>
class ComponentIndicesManager
{
public:
    ComponentIndicesManager()
    {
        (typeTag.get<ComponentTypes>(), ...);
    }

    template<typename... EntityComponentTypes>
    void addToEntity(Entity entity)
    {
        if (!entityIndices.contains(entity.id)) {
            entityIndices.insert(entity.id);
            entityComponentIndices.push_back(ComponentIndices{ });
        }
        auto& componentIndices = entityComponentIndices[entityIndices.getIndex(entity.id)];
        (componentIndices.addComponentIndex(typeTag.get<EntityComponentTypes>()), ...);
    }

    template<typename... EntityComponentTypes>
    void removeFromEntity(Entity entity)
    {
        if (!entityIndices.contains(entity.id))
            return;
        auto& componentIndices = entityComponentIndices[entityIndices.getIndex(entity.id)];
        (componentIndices.removeComponentIndex(typeTag.get<EntityComponentTypes>()), ...);
    }

    void removeEntity(Entity entity)
    {
        if (!entityIndices.contains(entity.id))
            return;
        size_t index = entityIndices.getIndex(entity.id);
        entityComponentIndices.erase(entityComponentIndices.begin() + index);
        entityIndices.remove(entity.id);
    }

    const std::vector<size_t>& getComponentIndices(Entity entity) const
    {
        if (!entityIndices.contains(entity.id))
            throw std::runtime_error("Entity not found in ComponentIndicesManager!");
        return entityComponentIndices[entityIndices.getIndex(entity.id)].getComponentIndices();
    }

private:
    SparseSet<EntityID> entityIndices;
    std::vector<ComponentIndices> entityComponentIndices;
    TypeTag typeTag;
};