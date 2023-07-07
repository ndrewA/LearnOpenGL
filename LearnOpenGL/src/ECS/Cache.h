#pragma once

#include <optional>
#include <vector>

#include "TypeTag.h"

template <typename ResultType>
class Cache 
{
public:
    template <typename... ComponentTypes>
    void store(const ResultType& result) 
    { 
        size_t index = VariadicTypeTag<ComponentTypes...>::index;
        if (index >= cache.size())
            cache.resize(index + 1);
        cache[index] = result;
    }

    template <typename... ComponentTypes>
    std::optional<ResultType> retrieve() const 
    {
        size_t index = VariadicTypeTag<ComponentTypes...>::index;
        return index < cache.size() ? cache[index] : std::nullopt;
    }

    void clear() 
    { 
        cache.clear(); 
    }

private:
    inline static std::vector<std::optional<ResultType>> cache;
};