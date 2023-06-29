#pragma once

#include <memory>
#include <typeindex>

#include "ComponentPool.h"
#include "EntityLifecycleManager.h"

#include "Entity.h"

class EntityManager
{
public:
    Entity createEntity()
    {
        return lifecycleManager.createEntity();
    }

    void destroyEntity(const Entity entity)
    {
        lifecycleManager.destroyEntity(entity);

        for (auto& [type, pool] : componentPools)
            pool->destroyEntity(entity);
    }

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

    template<typename... ComponentTypes>
    requires (std::derived_from<ComponentTypes, Component> && ...)
    std::vector<Entity> getEntitiesWithComponents() 
    {
        std::vector<Entity> entities;

        const auto& activeEntites = lifecycleManager.getActiveEntities();
        for (const auto& entity : activeEntites)
            if ((hasComponent<ComponentTypes>(entity) && ...))
                entities.push_back(entity);

        return entities;
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

        return *static_cast<ComponentPool<ComponentType>*>(it->second.get());
    }

private:
    std::unordered_map<std::type_index, std::unique_ptr<BaseComponentPool>> componentPools;
    EntityLifecycleManager lifecycleManager;
};