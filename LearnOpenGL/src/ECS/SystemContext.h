#pragma once

#include <iterator>

#include "ComponentManager.h"
#include "EntityManager.h"
#include "ArchetypeQuery.h"
#include "Cache.h"

class SystemContext
{
public:
    template<typename... ComponentTypes>
    using updateFn = std::function<void(Entity entity, ComponentTypes&...)>;

    SystemContext(EntityManager& entityManager, ComponentManager& componentManager, ArchetypeQuery archetypeManager)
        : entityManager(entityManager), componentManager(componentManager), archetypeQuery(archetypeManager) { }

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
        auto cachedEntities = entitiesCache.retrieve<ComponentTypes...>();
        if (cachedEntities) {
            for (Entity entity : *cachedEntities) 
                update(entity, componentManager.getComponent<ComponentTypes>(entity)...);
        }
        else {
            std::vector<Entity> entities = archetypeQuery.findCommonEntities<ComponentTypes...>();

            entitiesCache.store<ComponentTypes...>(entities);
            for (Entity entity : entities) 
                update(entity, componentManager.getComponent<ComponentTypes>(entity)...);
        }
    }

private:
    EntityManager& entityManager;
    ComponentManager& componentManager;
    ArchetypeQuery archetypeQuery;
    Cache<std::vector<Entity>> entitiesCache;
};