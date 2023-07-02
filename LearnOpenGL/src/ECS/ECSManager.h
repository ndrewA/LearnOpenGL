#pragma once

#include "SystemManager.h"

#include "EntityKey.h"

class ECSManager
{
public:
    ECSManager()
        : systemManager({ entityManager, componentManager, archetypeManager }) { }

    EntityKey createEntity()
    {
        return { entityManager.createEntity() };
    }

    void removeEntity(const EntityKey& key)
    {
        componentManager.removeEntity(key.getEntity());
        archetypeManager.removeEntity(key.getEntity());
        entityManager.removeEntity(key.getEntity());
    }

    template<typename ComponentType, typename... Args>
    void addComponent(const EntityKey& key, Args&&... args)
    {
        componentManager.addComponent<ComponentType>(key.getEntity(), std::forward(args)...);
        archetypeManager.addComponent<ComponentType>(key.getEntity());
    }

    template<typename ComponentType, typename... Args>
    void removeComponent(const EntityKey& key, Args&&... args)
    {
        componentManager.addComponent<ComponentType>(key.getEntity(), std::forward(args)...);
        archetypeManager.addComponent<ComponentType>(key.getEntity());
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