#pragma once

#include <typeindex>

#include "ComponentPool.h"

class ComponentManager
{
public:
    template<typename ComponentType, typename... Args>
    requires std::derived_from<ComponentType, Component>
    void addComponent(const Entity entity, Args&&... args)
    {
        auto component = std::make_unique<ComponentType>(std::forward(args)...);
        getComponentPool<ComponentType>().addComponent(entity, std::move(component));
    }

    template<typename ComponentType>
    requires std::derived_from<ComponentType, Component>
    const ComponentType& getComponent(const Entity entity) 
    {
        return getComponentPool<ComponentType>().getComponent(entity);
    }

    template<typename ComponentType>
    requires std::derived_from<ComponentType, Component>
    bool hasComponent(const Entity entity) 
    {
        return getComponentPool<ComponentType>().hasComponent(entity);
    }

    void destroyEntityComponents(const Entity entity)
    {
        for (auto& [type, pool] : componentPools)
            pool->destroyEntityComponent(entity);
    }

private:
    template<typename ComponentType>
    ComponentPool<ComponentType>& getComponentPool()
    {
        const std::type_index typeIndex(typeid(ComponentType));

        auto it = componentPools.find(typeIndex);
        if (it == componentPools.end()) {
            auto newPool = std::make_unique<ComponentPool<ComponentType>>();
            it = componentPools.emplace(typeIndex, std::move(newPool)).first;
        }

        return static_cast<ComponentPool<ComponentType>&>(*it->second.get());
    }

private:
    std::unordered_map<std::type_index, std::unique_ptr<BaseComponentPool>> componentPools;
};