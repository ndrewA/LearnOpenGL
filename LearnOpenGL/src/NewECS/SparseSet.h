#pragma once

#include <vector>
#include <stdexcept>

#include "Entity.h"

template <typename T>
requires std::is_integral_v<T>
class SparseSet
{
    static constexpr T INVALID_ITEM = std::numeric_limits<T>::max();

public:
    void insert(T item)
    {
        if (item >= sparse.size())
            sparse.resize(item + 10, INVALID_ITEM);
        dense.push_back(item);
        sparse[item] = dense.size() - 1;
    }

    void remove(T item)
    {
        if (!contains(item))
            return;
        T last = dense.back();
        dense[sparse[item]] = last;
        sparse[last] = sparse[item];
        dense.pop_back();
        sparse[item] = INVALID_ITEM;
    }

    size_t getIndex(T item) const
    {
        if (contains(item))
            return sparse[item];
        throw std::runtime_error("Item not found in sparse set!");
    }

    bool contains(T item) const
    {
        return item < sparse.size() && sparse[item] < dense.size() && dense[sparse[item]] == item;
    }

    const std::vector<T>& getItems() const
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
    std::vector<T> sparse;
    std::vector<T> dense;
};


