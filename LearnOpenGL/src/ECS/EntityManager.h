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
    }

    template<typename ComponentType, typename... Args>
    requires std::derived_from<ComponentType, Component>
    void addComponent(const Entity entity, Args&&... args)
    {
        auto component = std::make_shared<ComponentType>(std::forward(args)...);
        getComponentPool<ComponentType>().addComponent(entity, component);
    }

    template<typename ComponentType>
    requires std::derived_from<ComponentType, Component>
    std::shared_ptr<ComponentType> getComponent(const Entity entity)
    {
        return std::static_pointer_cast<ComponentType>(getComponentPool<Component>().getComponent(entity));
    }

    template<typename ComponentType>
    requires std::derived_from<ComponentType, Component>
    bool hasComponent(const Entity entity) 
    {
        return getComponentPool<ComponentType>().hasComponent(entity);
    }

    template<typename... Components>
    requires (std::derived_from<Components, Component> && ...)
    std::vector<Entity> getEntitiesWithComponents() 
    {
        std::vector<Entity> entities;

        const auto& activeEntites = lifecycleManager.getActiveEntities();
        for (const auto& entity : activeEntites)
            if ((hasComponent<Components>(entity) && ...))
                entities.push_back(entity);

        return entities;
    }

private:
    template<typename ComponentType>
    BaseComponentPool& getComponentPool()
    {
        const std::type_index typeIndex(typeid(ComponentType));

        auto it = componentPools.find(typeIndex);
        if (it == componentPools.end()) 
            it = componentPools.emplace(typeIndex, std::make_unique<ComponentPool<ComponentType>>()).first;

        return *it->second;
    }

private:
    std::unordered_map<std::type_index, std::unique_ptr<BaseComponentPool>> componentPools;
    EntityLifecycleManager lifecycleManager;
};