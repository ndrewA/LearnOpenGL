#pragma once

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
    ComponentType& getComponent(Entity entity)
    {
        return getComponentPool<ComponentType>().getComponent(entity);
    }

    template<typename ComponentType>
    bool hasComponent(Entity entity) 
    {
        return getComponentPool<ComponentType>().hasComponent(entity);
    }

    void removeEntity(Entity entity)
    {
        for (auto& pool : componentPools)
            pool->removeComponent(entity);
    }

    template<typename ComponentType>
    void removeComponent(Entity entity)
    {
        getComponentPool<ComponentType>().removeComponent(entity);
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
    inline static std::vector<std::unique_ptr<BaseComponentPool>> componentPools;
};