#pragma once

#include <unordered_map>
#include <vector>
#include <memory>
#include <typeindex>
#include <unordered_set>

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

    template<typename Component>
    void addComponent(const Entity entity, const std::shared_ptr<Component>& component)
    {
        getComponentPool<Component>().addComponent(entity, component);
    }

    template<typename Component>
    std::shared_ptr<Component> getComponent(const Entity entity) 
    {
        return std::static_pointer_cast<Component>(getComponentPool<Component>().getComponent(entity));
    }

    template<typename Component>
    bool hasComponent(Entity entity) 
    {
        return getComponentPool<Component>().hasComponent(entity);
    }

    template<typename... Components>
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
    template<typename Component>
    BaseComponentPool& getComponentPool()
    {
        const std::type_index typeIndex(typeid(Component));

        auto it = componentPools.find(typeIndex);
        if (it == componentPools.end()) 
            it = componentPools.emplace(typeIndex, std::make_unique<ComponentPool<Component>>()).first;

        return *it->second;
    }

private:
    std::unordered_map<std::type_index, std::unique_ptr<BaseComponentPool>> componentPools;
    EntityLifecycleManager lifecycleManager;
};