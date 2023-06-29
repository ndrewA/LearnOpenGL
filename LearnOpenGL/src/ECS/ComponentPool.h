#pragma once

#include <stdexcept>
#include <vector>
#include <memory>

#include "Component.h"
#include "ComponentPoolExceptions.h"

class BaseComponentPool
{
public:
    virtual ~BaseComponentPool() = default;
    virtual void destroyEntityComponent(const Entity) = 0;
    virtual bool hasComponent(const Entity entity) const = 0;
};

template <typename ComponentType>
class ComponentPool : public BaseComponentPool
{
public:
    void addComponent(const Entity entity, std::unique_ptr<ComponentType> component)
    {
        if (entity >= pool.size())
            pool.resize(entity + 1);

        pool[entity] = std::move(component);
    }

    void destroyEntityComponent(const Entity entity) override
    {
        if (entity < pool.size())
            pool[entity].reset();
    }

    const ComponentType& getComponent(const Entity entity) const
    {
        if (entity >= pool.size() || pool[entity] == nullptr)
            throw ComponentEntityNotFoundException(entity, typeid(ComponentType).name());

        return *pool[entity];
    }

    bool hasComponent(const Entity entity) const override
    {
        return entity < pool.size() && pool[entity] != nullptr;
    }

private:
    std::vector<std::unique_ptr<ComponentType>> pool;
};