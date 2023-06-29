#pragma once

#include "SystemManager.h"

class ECSManager
{
public:
    ECSManager()
        : context(lifecycleManager, componentManager) { }

    Entity createEntity()
    {
        return lifecycleManager.createEntity();
    }

    void destroyEntity(const Entity entity)
    {
        componentManager.destroyEntityComponents(entity);
        lifecycleManager.destroyEntity(entity);
    }

    template<typename ComponentType, typename... Args>
    requires std::derived_from<ComponentType, Component>
    void addComponent(const Entity entity, Args&&... args)
    {
        componentManager.addComponent<ComponentType>(entity, std::forward(args)...);
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
    void enableSystem(const bool enabled)
    {
        systemManager.enableSystem<SystemType>(enabled);
    }

    void updateSystems(const float deltaTime) 
    {
        systemManager.updateSystems(deltaTime, context);
    }

private:
    EntityLifecycleManager lifecycleManager;
    ComponentManager componentManager;
    SystemManager systemManager;
    SystemContext context;
};