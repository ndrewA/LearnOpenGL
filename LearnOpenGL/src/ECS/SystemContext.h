#pragma once

#include <iterator>
#include <functional>

#include "ComponentManager.h"
#include "EntityManager.h"
#include "Cache.h"

class SystemContext
{
public:
    template<typename... ComponentTypes>
    using UpdateFn = std::function<void(Entity entity, ComponentTypes&...)>;

    SystemContext(const EntityManager& entityManager, ComponentManager& componentManager)
        : entityManager(entityManager), componentManager(componentManager) { }

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
        //archetypeManager.addComponent<ComponentType>(entity);
    } 

    template<typename... ComponentTypes>
    void updateEntitiesWithComponents(const UpdateFn<ComponentTypes...>& update) const
    {
        //for (auto entity : archetypeManager.findCommonEntities<ComponentTypes...>())
        //    update(entity, componentManager.getComponent<ComponentTypes>(entity)...);
    }

private:
    const EntityManager& entityManager;
    ComponentManager& componentManager;
};