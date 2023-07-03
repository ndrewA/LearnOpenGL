#pragma once

#include "SystemManager.h"

#include "EntityKey.h"

class ECSManager
{
public:
    ECSManager()
        : systemManager( SystemContext{ entityManager, componentManager, archetypeManager } ) { }

    EntityKey createEntity()
    {
        archetypeManager.clearCache();
        return { entityManager.createEntity() };
    }

    template<typename ComponentType, typename... Args>
    void addComponent(const EntityKey& key, Args&&... args)
    {
        Entity entity = key.getEntity();
        componentManager.addComponent<ComponentType>(entity, std::forward(args)...);
        archetypeManager.addComponent<ComponentType>(entity);
    }

    void removeEntity(const EntityKey& key)
    {
        Entity entity = key.getEntity();
        componentManager.removeEntity(entity);
        archetypeManager.removeEntity(entity);
        entityManager.removeEntity(entity);
    }

    template<typename ComponentType>
    void removeComponent(const EntityKey& key)
    {
        Entity entity = key.getEntity();
        componentManager.removeComponent<ComponentType>(entity);
        archetypeManager.removeComponent<ComponentType>(entity);
    }

    template<typename SystemType, typename... Args>
    requires std::derived_from<SystemType, System>
    void addSystem(Args&&... args)
    {
        systemManager.addSystem<SystemType>(std::forward<Args>(args)...);
    }

    template<typename SystemType>
    requires std::derived_from<SystemType, System>
    void removeSystem()
    {
        systemManager.removeSystem<SystemType>();
    }

    template<typename SystemType>
    requires std::derived_from<SystemType, System>
    bool hasSystem() const
    {
        return systemManager.hasSystem<SystemType>();
    }

    template<typename SystemType>
    requires std::derived_from<SystemType, System>
    void enableSystem(bool enabled)
    {
        systemManager.enableSystem<SystemType>(enabled);
    }

    void updateSystems(float deltaTime) 
    {
        systemManager.updateSystems(deltaTime);
    }

private:
    EntityManager entityManager;
    ComponentManager componentManager;
    ArchetypeManager archetypeManager;
    SystemManager systemManager;
};