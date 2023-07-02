#pragma once

#include <stdexcept>
#include <memory>
#include <optional>

#include "EntityExceptions.h"
#include "ComponentPoolExceptions.h"

class BaseComponentPool
{
public:
    virtual ~BaseComponentPool() = default;
    virtual void removeEntityComponent(Entity entity) = 0;
    virtual bool hasComponent(Entity entity) const = 0;
};

template <typename ComponentType>
class ComponentPool : public BaseComponentPool
{
public:
    template<typename... Args>
    void addComponent(Entity entity, Args&&... args)
    {
        if (entity.index >= pool.size())
            pool.resize(entity.index + 1);

        pool[entity.index] = ComponentType(std::forward<Args>(args)...);
    }

    void removeEntityComponent(Entity entity) override
    {
        if (entity.index >= pool.size())
            return;

        pool[entity.index] = std::move(pool.back());
        pool.pop_back();
    }

    ComponentType& getComponent(Entity entity) const
    {
        if (entity.index >= pool.size())
            throw EntityOutOfBoundsException(entity);

        if (!pool[entity.index])
            throw ComponentOutOfBoundsException(entity, typeid(ComponentType).name());

        return *pool[entity.index];
    }

    bool hasComponent(Entity entity) const override
    {
        return entity.index < pool.size() && pool[entity.index].has_value();
    }

private:
    std::vector<std::optional<ComponentType>> pool;
};