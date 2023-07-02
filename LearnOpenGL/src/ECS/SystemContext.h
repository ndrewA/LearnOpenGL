#pragma once

#include <iterator>

#include "ComponentManager.h"
#include "EntityManager.h"
#include "ArchetypeManager.h"

class SystemContext
{
public:
    template<typename... ComponentTypes>
    using updateFn = std::function<void(Entity entity, ComponentTypes&...)>;

    SystemContext(EntityManager& entityManager, ComponentManager& componentManager, ArchetypeManager& archetypeManager)
        : entityManager(entityManager), componentManager(componentManager), archetypeManager(archetypeManager)  { }

    template<typename ComponentType>
    bool hasComponent(Entity entity) const
    {
        return componentManager.hasComponent<ComponentType>(entity);
    }

    template<typename ComponentType>
    const ComponentType& getComponent(Entity entity) const
    {
        return componentManager.getComponent<ComponentType>(entity);
    }

    template<typename... ComponentTypes>
    void updateEntitiesWithComponents(const updateFn<ComponentTypes...>& update) const
    {
        std::vector<std::set<Entity>> entitySets = { archetypeManager.getEntities<ComponentTypes>()... };

        for (const Entity& entity : findCommonEntities(entitySets)) 
            update(entity, componentManager.getComponent<ComponentTypes>(entity)...);
    }

private:
    std::set<Entity> findCommonEntities(const std::vector<std::set<Entity>>& entitySets)
    {
        if (entitySets.empty())
            return {};

        auto smallestSetIt = std::min_element(entitySets.begin(), entitySets.end(),
            [](const std::set<Entity>& a, const std::set<Entity>& b) {
                return a.size() < b.size();
            });

        std::set<Entity> commonEntities = *smallestSetIt;

        for (auto it = entitySets.begin(); it != entitySets.end(); ++it)
        {
            if (it == smallestSetIt)
                continue;

            std::set<Entity> intersection;
            std::set_intersection(commonEntities.begin(), commonEntities.end(),
                it->begin(), it->end(),
                std::inserter(intersection, intersection.begin()));

            commonEntities = std::move(intersection);
        }

        return commonEntities;
    }

private:
    EntityManager& entityManager;
    ComponentManager& componentManager;
    ArchetypeManager& archetypeManager;
};