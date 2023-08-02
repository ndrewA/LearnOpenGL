#pragma once

#include "SparseSet.h"
#include "TypeTag.h"

class ComponentIndices
{
public:
    void addComponentIndex(size_t index)
    {
        componentIndices.insert(index);
    }

    void removeComponentIndex(size_t index)
    {
        componentIndices.remove(index);
    }

    const std::vector<size_t>& getComponentIndices() const
    {
        return componentIndices.getItems();
    }

    auto begin() { return componentIndices.begin(); }
    auto end() { return componentIndices.end(); }

private:
    SparseSet<size_t> componentIndices;
};