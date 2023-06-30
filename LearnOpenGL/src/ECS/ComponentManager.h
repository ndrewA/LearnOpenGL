#pragma once

#include <typeindex>

#include "ComponentPool.h"

class ComponentManager
{
public:
    template<typename ComponentType, typename... Args>
    void addComponent(Entity entity, Args&&... args)
    {
        auto component = std::make_unique<ComponentType>(std::forward(args)...);
        getComponentPool<ComponentType>().addComponent(entity, std::move(component));
    }

    template<typename ComponentType>
    const ComponentType& getComponent(Entity entity) 
    {
        return getComponentPool<ComponentType>().getComponent(entity);
    }

    template<typename ComponentType>
    bool hasComponent(Entity entity) 
    {
        return getComponentPool<ComponentType>().hasComponent(entity);
    }

    void destroyEntityComponents(Entity entity)
    {
        for (auto& [type, pool] : componentPools)
            pool->destroyEntityComponent(entity);
    }

private:
    template<typename ComponentType>
    ComponentPool<ComponentType>& getComponentPool()
    {
        std::type_index typeIndex(typeid(ComponentType));

        auto it = componentPools.find(typeIndex);
        if (it == componentPools.end()) {
            auto newPool = std::make_unique<ComponentPool<ComponentType>>();
            it = componentPools.emplace(typeIndex, std::move(newPool)).first;
        }

        return static_cast<ComponentPool<ComponentType>&>(*it->second);
    }

private:
    std::unordered_map<std::type_index, std::unique_ptr<BaseComponentPool>> componentPools;
};