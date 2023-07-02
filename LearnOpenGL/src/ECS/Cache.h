#pragma once

#include <optional>
#include <unordered_map>

#include "TypeTag.h"

template <typename ResultType>
class Cache {
public:
    template <typename... ComponentTypes>
    void store(const ResultType& result) { cache[VariadicTypeTag<ComponentTypes...>::index] = result;  }

    template <typename... ComponentTypes>
    std::optional<ResultType> retrieve() const {
        auto it = cache.find(VariadicTypeTag<ComponentTypes...>::index);
        return (it != cache.end()) it->second : std::nullopt;
    }

    void clear() { cache.clear(); }

private:
    std::unordered_map<size_t, ResultType> cache;
};