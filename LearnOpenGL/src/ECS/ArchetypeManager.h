#pragma once

#include "Cache.h"
#include "ArchetypeQuery.h"

class ArchetypeManager
{
public:
    ArchetypeManager()
        : archetypeQuery(archetypeStorage) { }

    template<typename ComponentType>
    void addComponent(Entity entity)
    {
        archetypeStorage.addComponent<ComponentType>(entity);
        cache.clear();
    }

    template<typename ComponentType>
    void removeComponent(Entity entity)
    {
        archetypeStorage.removeComponent<ComponentType>(entity);
        cache.clear();
    }

    void removeEntity(Entity entity)
    {
        archetypeStorage.removeEntity(entity);
        cache.clear();
    }

    template<typename ComponentType>
    const std::unordered_set<Entity>& getEntities() const
    {
        return archetypeStorage.getEntities<ComponentType>();
    }

    template<typename... ComponentTypes>
    std::unordered_set<Entity> findCommonEntities()
    {
        auto cachedEntities = cache.retrieve<ComponentTypes...>();
        if (cachedEntities) {
            return *cachedEntities;
        }
        else {
            std::unordered_set<Entity> entities = archetypeQuery.findCommonEntities<ComponentTypes...>();
            cache.store<ComponentTypes...>(entities);
            return entities;
        }
    }

    void clearCache() 
    {
        cache.clear();
    }

private:
    ArchetypeStorage archetypeStorage;
    ArchetypeQuery archetypeQuery;
    Cache<std::unordered_set<Entity>> cache;
};