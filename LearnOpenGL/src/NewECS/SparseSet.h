#pragma once

#include <vector>
#include <stdexcept>

#include "Entity.h"

template<typename T = Entity>
class SparseSet
{
    static constexpr size_t INVALID_ENTITY = std::numeric_limits<size_t>::max();

public:
    void insert(Entity entity)
    {
        EntityID id = entity.id;
        if (id >= sparse.size())
            sparse.resize(id + 10, INVALID_ENTITY);
        dense.push_back(entity);
        sparse[id] = dense.size() - 1;
    }

    void remove(Entity entity)
    {
        EntityID id = entity.id;
        if (contains(entity) == false)
            return;
        Entity last = dense.back();
        dense[sparse[id]] = last;
        sparse[last.id] = sparse[id];
        dense.pop_back();
        sparse[id] = INVALID_ENTITY;
    }

    size_t getIndex(Entity entity) const
    {
        if (contains(entity))
            return sparse[entity.id];
        throw std::runtime_error("Entity not found in sparse set!");
    }

    bool contains(Entity entity) const
    {
        EntityID id = entity.id;
        return id < sparse.size() && sparse[id] < dense.size() && dense[sparse[id]].id == id;
    }

    const std::vector<Entity>& getEntities() const 
    {
        return dense;
    }

    auto begin()
    {
        return dense.begin();
    }

    auto end()
    {
        return dense.end();
    }

    size_t size() const
    {
        return dense.size();
    }

private:
    std::vector<EntityID> sparse;
    std::vector<Entity> dense;
};
