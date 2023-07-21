#pragma once

#include <type_traits>

template <typename SystemType>
concept HasUpdate = requires(SystemType system)
{
    { system.update };
};
