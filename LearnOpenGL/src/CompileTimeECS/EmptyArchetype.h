#pragma once

#include "Archetype.h"

template <>
class Archetype<> : public BaseArchetype
{
public:
    using Entity = Entity<>;
    using ComponentsTuple = std::tuple<>;

    void addEntity(Entity entity, ComponentsTuple components)
    {
    }

    ComponentsTuple removeEntityAndGetComponents(Entity entity)
    {
        return ComponentsTuple{};
    }

    template <typename Function>
    void forEachEntity(Function function)
    { 
    }
};
