#pragma once

#include <tuple>
#include <vector>
#include <functional>

#include "ComponentBuffer.h"

template <typename... ComponentTypes>
class ComponentRemover
{
public:
    ComponentRemover(std::tuple<ComponentBuffer<ComponentTypes>...>& componentBuffers)
    {
        createRemoveComponentFuncs(componentBuffers);
    }

    void removeComponent(Entity entity, size_t index)
    {
        if (index >= removeComponentFuncs.size())
            throw std::out_of_range("index out of bounds!");

        removeComponentFuncs[index](entity);
    }

private:
    void createRemoveComponentFuncs(std::tuple<ComponentBuffer<ComponentTypes>...>& componentBuffers)
    {
        std::apply(
            [&](auto&&... args) {
                ((removeComponentFuncs.push_back(
                    [&args](Entity entity) {
                        args.removeComponent(entity);
                    })), ...);
            },
            componentBuffers);
    }

private:
    std::vector<std::function<void(Entity)>> removeComponentFuncs;
};
