#pragma once

#include "SparseSet.h"

template<typename... SystemTypes>
class EntitySubscription
{
public:
    template<typename SystemType>
    void subscribe(Entity entity)
    {
        // Add entity to the sparse set for SystemType
    }

    template<typename SystemType>
    void unsubscribe(Entity entity)
    {
        // Remove entity from the sparse set for SystemType
    }

private:
    // A sparse set for each system type
    std::tuple<SparseSet<SystemTypes>...> systemSets;
};