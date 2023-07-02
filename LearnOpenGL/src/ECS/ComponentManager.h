#pragma once

#include <typeindex>

#include "ComponentPool.h"
#include "TypeTag.h"

class ComponentManager
{
public:
    template<typename ComponentType, typename... Args>
    void addComponent(Entity entity, Args&&... args)
    {
        getComponentPool<ComponentType>().addComponent(entity, std::forward(args)...);
    }

    template<typename ComponentType>
    ComponentType& getComponent(Entity entity) const
    {
        return getComponentPool<ComponentType>().getComponent(entity);
    }

    template<typename ComponentType>
    bool hasComponent(Entity entity) 
    {
        return getComponentPool<ComponentType>().hasComponent(entity);
    }

    template<typename ComponentType>
    void removeComponent(Entity entity)
    {
        getComponentPool<ComponentType>().removeEntityComponent(entity);
    }

    void removeEntity(Entity entity)
    {
        for (auto& pool : componentPools)
            pool->removeEntityComponent(entity);
    }

private:
    template<typename ComponentType>
    ComponentPool<ComponentType>& getComponentPool()
    {
        size_t index = ComponentTypeTag<ComponentType>::index;

        if (index >= componentPools.size())
            componentPools.resize(index + 1);

        if (componentPools[index] == nullptr)
            componentPools[index] = std::make_unique<ComponentPool<ComponentType>>();

        return static_cast<ComponentPool<ComponentType>&>(*componentPools[index]);
    }

private:
    std::vector<std::unique_ptr<BaseComponentPool>> componentPools;
};