#pragma once

#include "Entity.h"
#include "SparseSet.h"

#include <vector>
#include <stdexcept>

class BaseArchetype
{
public:
    virtual ~BaseArchetype() = default;
};

template <typename... ComponentTypes>
class Archetype : public BaseArchetype
{
public:
    using Entity = Entity<ComponentTypes...>;
    using ComponentsTuple = std::tuple<ComponentTypes...>;

    void addEntity(Entity entity, ComponentsTuple components)
    {
        if (entities.contains(entity))
            throw std::runtime_error("Entity already added to archetype!");

        entities.insert(entity);

        std::apply([this](auto&&... component) {
            ((std::get<std::vector<std::decay_t<decltype(component)>>>(componentsData).push_back(std::move(component))), ...);
            }, std::move(components)); // moves from one tuple to another
    }

    ComponentsTuple removeEntityAndGetComponents(Entity entity)
    {
        if (!entities.contains(entity))
            throw std::runtime_error("Entity not found in archetype!");

        auto components = getEntityComponents(entity);

        removeEntityComponents(entity);
        entities.remove(entity);

        return components;
    }

    template <typename... RequiredComponentTypes, typename Function>
    void forEachEntity(Function function)
    {
        for (size_t i = 0; i < entities.size(); ++i)
            function(entities[i], std::get<std::vector<RequiredComponentTypes>>(componentsData)[i]...);
    }

private:
    ComponentsTuple getEntityComponents(Entity entity)
    {
        if (!entities.contains(entity))
            throw std::runtime_error("Entity not found in archetype!");

        return std::make_tuple(std::get<std::vector<ComponentTypes>>(componentsData)[entities.getIndex(entity)]...);
    }

    void removeEntityComponents(Entity entity)
    {
        size_t index = entities.getIndex(entity);
        (std::get<std::vector<ComponentTypes>>(componentsData)
            .erase(std::get<std::vector<ComponentTypes>>(componentsData).begin() + index), ...);
    }

private:
    SparseSet<ComponentTypes...> entities;
    std::tuple<std::vector<ComponentTypes>...> componentsData;
};