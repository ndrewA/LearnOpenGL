#pragma once

#include <bitset>

#include "SparseSet.h"
#include "TypeTag.h"
#include "Signature.h"

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
            signatures.resize(entityIndex + 10);

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
    }

    void removeEntity(Entity entity)
    {
        size_t entityIndex = entities.getIndex(entity.id);

        if (entityIndex >= signatures.size())
            throw std::out_of_range("Entity index is out of range!");

        signatures.erase(signatures.begin() + entityIndex);
        entities.remove(entity.id);
    }

    template<typename ComponentType>
    bool hasComponent(Entity entity) const
    {
        size_t componentIndex = componentTypeTag.get<ComponentType>();
        size_t entityIndex = entities.getIndex(entity);

        if (entityIndex >= signatures.size())
            throw std::out_of_range("Entity index is out of range!");

        return signatures[entityIndex].test(componentIndex);
    }

    Signature getSignature(Entity entity) const
    {
        size_t entityIndex = entities.getIndex(entity.id);

        if (entityIndex >= signatures.size())
            throw std::out_of_range("Entity index is out of range!");

        return signatures[entityIndex];
    }

private:
    template<typename ComponentType>
    void addComponent(Entity entity)
    {
        size_t componentIndex = componentTypeTag.get<ComponentType>();
        size_t entityIndex = entities.getIndex(entity.id);

        if (entityIndex >= signatures.size())
            throw std::out_of_range("Entity index is out of range!");
        
        signatures[entityIndex].set(componentIndex);
    }

private:
    SparseSet<EntityID> entities;
    std::vector<Signature> signatures;
    TypeTag componentTypeTag;
};