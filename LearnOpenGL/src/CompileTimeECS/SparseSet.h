#pragma once

#include <vector>
#include <stdexcept>

#include "Entity.h"

template <typename... ComponentTypes>
class SparseSet 
{
public:
    using Entity = Entity<ComponentTypes...>;

    void insert(Entity entity) 
    {
        size_t ID = entity.ID;
        if (ID >= sparse.size())
            sparse.resize(ID + 1, std::numeric_limits<size_t>::max());
        dense.push_back(entity);
        sparse[ID] = dense.size() - 1;
    }

    void remove(Entity entity)
    {
        size_t ID = entity.ID;
        if (contains(entity) == false)
            return;
        Entity last = dense.back();
        dense[sparse[ID]] = last;
        sparse[last.ID] = sparse[ID];
        dense.pop_back();
        sparse[ID] = std::numeric_limits<size_t>::max();
    }

    size_t size() const
    {
        return dense.size();
    }

    Entity operator[](size_t index) const
    {
        if (index >= dense.size())
            throw std::out_of_range("Index out of range!");
        return dense[index];
    }

    size_t getIndex(Entity entity) const
    {
        if (contains(entity))
            return sparse[entity.ID];
        throw std::runtime_error("Entity not found in sparse set!");
    }

    bool contains(Entity entity) const 
    {
        size_t ID = entity.ID;
        return ID < sparse.size() && sparse[ID] < dense.size() && dense[sparse[ID]].ID == ID;
    }

private:
    std::vector<size_t> sparse;
    std::vector<Entity> dense; 
};
