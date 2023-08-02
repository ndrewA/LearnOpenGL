#pragma once

#include <bitset>

#include "SparseSet.h"
#include "TypeTag.h"
#include "Signature.h"
#include "ComponentIndices.h"

template <size_t N>
class EntityMetadata
{
    using Signature = EntitySignature<N>;

public:
    template<typename... ComponentTypes>
    void addToEntity(Entity entity)
    {
        entities.insert(entity.id);
        size_t entityIndex = entities.getIndex(entity.id);

        if (entityIndex >= signatures.size())
        {
            signatures.resize(entityIndex + 1);
            componentIndices.resize(entityIndex + 1);
        }

        (addComponent<ComponentTypes>(entity), ...);
    }

    template<typename ComponentType>
    void removeFromEntity(Entity entity)
    {
        size_t componentIndex = componentTypeTag.get<ComponentType>();
        size_t entityIndex = entities.getIndex(entity.id);

        if (entityIndex >= signatures.size())
            throw std::out_of_range("Entity index is out of range!");

        signatures[entityIndex].reset(componentIndex);
        componentIndices[entityIndex].removeComponentIndex(componentIndex);
    }

    void removeEntity(Entity entity)
    {
        size_t entityIndex = entities.getIndex(entity.id);

        if (entityIndex >= signatures.size())
            throw std::out_of_range("Entity index is out of range!");

        entities.remove(entity.id);

        signatures.erase(signatures.begin() + entityIndex);
        componentIndices.erase(componentIndices.begin() + entityIndex);
    }

    template<typename ComponentType>
    bool hasComponent(Entity entity) const
    {
        if (!entities.contains(entity.id))
            throw std::out_of_range("Entity does not exist!");

        size_t componentIndex = componentTypeTag.get<ComponentType>();
        size_t entityIndex = entities.getIndex(entity);

        return signatures[entityIndex].test(componentIndex);
    }

    const Signature& getSignature(Entity entity) const
    {
        if (!entities.contains(entity.id))
            throw std::out_of_range("Entity does not exist!");

        size_t entityIndex = entities.getIndex(entity.id);

        return signatures[entityIndex];
    }

    const std::vector<size_t>& getIndices(Entity entity) const
    {
        if (!entities.contains(entity.id))
            throw std::out_of_range("Entity does not exist!");

        size_t entityIndex = entities.getIndex(entity.id);

        return componentIndices[entityIndex].getComponentIndices();
    }

private:
    template<typename ComponentType>
    void addComponent(Entity entity)
    {
        size_t componentIndex = componentTypeTag.get<ComponentType>();
        size_t entityIndex = entities.getIndex(entity.id);

        signatures[entityIndex].set(componentIndex);
        componentIndices[entityIndex].addComponentIndex(componentIndex);
    }

private:
    SparseSet<EntityID> entities;
    std::vector<Signature> signatures;
    std::vector<ComponentIndices> componentIndices;
    TypeTag componentTypeTag;
};
