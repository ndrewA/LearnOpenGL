#pragma once

#include <iterator>

#include "ComponentManager.h"
#include "EntityManager.h"
#include "ArchetypeManager.h"
#include "Cache.h"

class SystemContext
{
public:
    template<typename... ComponentTypes>
    using UpdateFn = std::function<void(Entity entity, ComponentTypes&...)>;

    SystemContext(const EntityManager& entityManager, 
                  ComponentManager& componentManager,  ArchetypeManager& archetypeManager)
        : entityManager(entityManager), 
          componentManager(componentManager), archetypeManager(archetypeManager) { }

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

    template<typename ComponentType, typename... Args>
    void createComponent(Entity entity, Args&&... args)
    {
        componentManager.addComponent<ComponentType>(entity, std::forward(args)...);
        archetypeManager.addComponent<ComponentType>(entity);
    } 

    template<typename... ComponentTypes>
    void updateEntitiesWithComponents(const UpdateFn<ComponentTypes...>& update) const
    {
        for (auto entity : archetypeManager.findCommonEntities<ComponentTypes...>())
            update(entity, componentManager.getComponent<ComponentTypes>(entity)...);
    }

private:
    const EntityManager& entityManager;
    ComponentManager& componentManager;
    ArchetypeManager& archetypeManager;
};