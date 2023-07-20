#pragma once

#include <bitset>

#include "SparseSet.h"
#include "TypeTag.h"

template <size_t ComponentCount>
class EntityMetadata
{
	using Signature = std::bitset<ComponentCount>;

public:
    template<typename ComponentType>
    void addComponent(Entity entity)
    {
        size_t componentIndex = TypeTag::get<ComponentType>();
        size_t entityIndex = entities.getIndex(entity);
        signatures[entityIndex].set(componentIndex);
    }

    template<typename ComponentType>
    void removeComponent(Entity entity)
    {
        size_t componentIndex = TypeTag::get<ComponentType>();
        size_t entityIndex = entities.getIndex(entity);
        signatures[entityIndex].reset(componentIndex);
    }

    template<typename ComponentType>
    bool hasComponent(Entity entity) const
    {
        size_t componentIndex = TypeTag::get<ComponentType>();
        size_t entityIndex = entities.getIndex(entity)
        return signatures[entityIndex].test(componentIndex);
    }

    template<typename... ComponentTypes>
    void addToEntity(Entity entity, ComponentTypes... components)
    {
        entities.insert(entity);
        size_t entityIndex = entities.getIndex(entity);
        signatures[entityIndex] = Signature{};
        
        (addComponent<ComponentTypes>(entity), ...);
    }

    void removeEntity(Entity entity)
    {
        size_t entityIndex = entities.getIndex(entity);
        signatures.erase(entityIndex);
        entities.remove(entity);
    }

private:
    SparseSet entities;
    std::vector<Signature> signatures;
};