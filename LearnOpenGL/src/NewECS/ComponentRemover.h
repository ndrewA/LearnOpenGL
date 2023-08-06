#pragma once

#include <tuple>
#include <array>
#include <functional>

#include "ComponentBuffer.h"

template <typename... ComponentTypes>
class ComponentRemover
{
public:
    static constexpr size_t COMPONENT_COUNT = sizeof...(ComponentTypes);
    using RemoveComponentFuncs = std::array<std::function<void(Entity)>, COMPONENT_COUNT>;

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
                size_t i = 0;
                ((removeComponentFuncs[i++] =
                    [&args](Entity entity) {
                        args.removeComponent(entity);
                    }), ...);
            },
            componentBuffers);
    }

private:
    RemoveComponentFuncs removeComponentFuncs;
};