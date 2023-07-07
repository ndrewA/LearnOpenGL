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
    virtual void removeComponent(Entity entity) = 0;
    virtual bool hasComponent(Entity entity) const = 0;
};

template <typename ComponentType>
class ComponentPool : public BaseComponentPool
{
public:
    template<typename... Args>
    void addComponent(Entity entity, Args&&... args)
    {
        if (entity.index >= sparse.size())
            sparse.resize(entity.index + 1, -1);

        dense.push_back(ComponentType(std::forward<Args>(args)...));
        sparse[entity.index] = dense.size() - 1;
    }

    void removeComponent(Entity entity) override
    {
        if (!hasComponent(entity))
            throw ComponentOutOfBoundsException(entity);

        size_t denseIndex = sparse[entity.index];
        std::swap(dense[denseIndex], dense.back());
        dense.pop_back();

        Entity swappedEntity = dense[denseIndex].entity;
        sparse[swappedEntity.index] = denseIndex;
        sparse[entity.index] = -1;
    }

    ComponentType& getComponent(Entity entity) const
    {
        if (!hasComponent(entity))
            throw ComponentOutOfBoundsException(entity);

        return dense[sparse[entity.index]];
    }

    bool hasComponent(Entity entity) const override
    {
        return entity.index < sparse.size() && sparse[entity.index] != -1;
    }

private:
    inline static std::vector<ComponentType> dense;
    inline static std::vector<size_t> sparse;
};