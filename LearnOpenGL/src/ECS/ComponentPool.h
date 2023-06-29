#pragma once

#include <stdexcept>
#include <unordered_map>
#include <memory>

#include "Component.h"
#include "Entity.h"

class BaseComponentPool
{
public:
    virtual ~BaseComponentPool() = default;
    virtual void destroyEntity(const Entity) = 0;
    virtual bool hasComponent(const Entity entity) const = 0;
};

template <typename ComponentType>
class ComponentPool : public BaseComponentPool
{
public:
    void addComponent(const Entity entity, std::unique_ptr<ComponentType> component)
    {
        pool[entity] = std::move(component);
    }

    void destroyEntity(const Entity entity) override
    {
        pool.erase(entity);
    }

    const ComponentType& getComponent(const Entity entity) const
    {
        auto it = pool.find(entity);
        if (it == pool.end())
            throw std::runtime_error("Pool doesn't contain entity!");

        return *it->second.get();
    }

    bool hasComponent(const Entity entity) const override
    {
        return pool.find(entity) != pool.end();
    }

private:
    std::unordered_map<Entity, std::unique_ptr<ComponentType>> pool;
};