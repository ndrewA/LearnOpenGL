#include "SparseSet.h"

#include <stdexcept>
#include <vector>

void SparseSet::insert(size_t key)
{
    if (key >= sparse.size())
        sparse.resize(key + 1, -1);
    if (key >= dense.size())
        dense.resize(key + 1, -1);

    dense[size] = key;
    sparse[key] = size;
    size++;
}

const std::vector<size_t>& SparseSet::getAll() const
{
    return dense;
}

bool SparseSet::has(size_t key) const
{
    return key < sparse.size() &&
        sparse[key] < size &&
        dense[sparse[key]] == key;
}

size_t SparseSet::get(size_t key) const
{
    if (has(key))
        return dense[sparse[key]];

    throw std::runtime_error("Key not found!");
}

void SparseSet::remove(size_t key)
{
    if (has(key) == false)
        return;
    dense[sparse[key]] = dense[size - 1];
    sparse[dense[size - 1]] = sparse[key];
    size--;
}