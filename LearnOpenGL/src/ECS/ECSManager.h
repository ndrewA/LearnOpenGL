#pragma once

#include "SystemManager.h"

class ECSManager
{
public:
    ECSManager()
        : context(IDManager, componentManager) { }

    Entity createEntity()
    {
        return IDManager.createEntity();
    }

    void destroyEntity(Entity entity)
    {
        componentManager.destroyEntityComponents(entity);
        IDManager.destroyEntity(entity);
    }

    template<typename ComponentType, typename... Args>
    requires std::derived_from<ComponentType, Component>
    void addComponent(Entity entity, Args&&... args)
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
    void enableSystem(bool enabled)
    {
        systemManager.enableSystem<SystemType>(enabled);
    }

    void updateSystems(float deltaTime) 
    {
        systemManager.updateSystems(deltaTime, context);
    }

private:
    EntityIDManager IDManager;
    ComponentManager componentManager;
    SystemManager systemManager;
    SystemContext context;
};