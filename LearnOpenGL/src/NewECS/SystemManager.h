#pragma once

#include <tuple>

template<typename... SystemTypes>
class SystemManager
{
public:
    SystemManager()
        : systems(std::make_tuple(SystemTypes()...)) { }

    void updateAll()
    {
        std::apply([](auto&... system) { (system.update(), ...); }, systems);
    }

    template<typename SystemType>
    void update()
    {
        return std::get<SystemType>(systems).update();
    }

private:
    std::tuple<SystemTypes...> systems;
};