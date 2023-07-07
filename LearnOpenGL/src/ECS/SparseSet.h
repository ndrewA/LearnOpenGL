#pragma once

#include <stdexcept>

template<typename T>
class SparseSet {
public:
    void insert(size_t key, T value) 
    {
        if (key >= sparse.size()) 
            sparse.resize(key + 1, -1);
        if (key >= dense.size()) 
            dense.resize(key + 1);

        dense[size] = value;
        sparse[key] = size;
        size++;
    }

    T get(size_t key) const
    {
        if (has(key))
            return dense[sparse[key]];
        
        throw std::runtime_error("Key not found!");
    }

    const std::vector<T>& getAll() const
    {
        return dense;
    }

    bool has(size_t key) const
    {
        return key < sparse.size() && 
               sparse[key] < size && 
               dense[sparse[key]].index == key;
    }

    void remove(size_t key) 
    {
        if (has(key) == false)
            return;
        dense[sparse[key]] = dense[size - 1];
        sparse[dense[size - 1]] = sparse[key];
        size--;
    }

private:
    std::vector<size_t> sparse;
    std::vector<T> dense;
    size_t size = 0;
};
