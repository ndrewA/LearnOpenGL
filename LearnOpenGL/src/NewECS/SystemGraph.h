#pragma once

template<typename... SystemNodes>
class SystemGraph
{
    using Systems = std::tuple<SystemNodes...>;
public:


private:
    Systems systems;
};
