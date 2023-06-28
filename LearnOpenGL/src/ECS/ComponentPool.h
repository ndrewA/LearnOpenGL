#pragma once

#include <stdexcept>
#include <unordered_map>

#include "Component.h"
#include "Entity.h"

class BaseComponentPool
{
public:
    virtual ~BaseComponentPool() = default;

    virtual void addComponent(const Entity entity, const std::shared_ptr<Component>& component) = 0;
    virtual void destroyEntity(const Entity entity) = 0;
    virtual std::shared_ptr<Component> getComponent(const Entity entity) const = 0;
    virtual bool hasComponent(const Entity entity) const = 0;
};

template <typename ComponentType>
class ComponentPool : public BaseComponentPool
{
public:
    void addComponent(const Entity entity, const std::shared_ptr<Component>& component) override
    {
        pool[entity] = component;
    }

    void destroyEntity(const Entity entity) override
    {
        pool.erase(entity);
    }

    std::shared_ptr<Component> getComponent(const Entity entity) const override
    {
        auto it = pool.find(entity);
        if (it == pool.end())
            return nullptr;

        return it->second;
    }

    bool hasComponent(const Entity entity) const override
    {
        return pool.find(entity) != pool.end();
    }

private:
    std::unordered_map<Entity, std::shared_ptr<Component>> pool;
};