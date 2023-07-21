#pragma once

#include <array>
#include <bitset>

#include "TypeTag.h"
#include "HasUpdate.h"
#include "ComponentCount.h"

template <typename... SystemTypes>
class SystemMetadata
{
    using Signature = std::bitset<ComponentCount<SystemTypes...>>;

public:
    SystemMetadata()
    {
        (setSignature<SystemTypes>(), ...);
    }

    bool matches(Signature entitySignature) const
    {
        return (systemSignature & entitySignature) == systemSignature;
    }

private:
    template<HasUpdate System>
    void setSignature()
    {
        using ArgTypes = typename FunctionTraits<decltype(&System::update)>::arg_types;

        setSignatureHelper<System>(std::make_index_sequence<std::tuple_size_v<ArgTypes>>{});
    }

    template<typename System, std::size_t... I>
    void setSignatureHelper(std::index_sequence<I...>)
    {
        (setComponentSignature<System, std::tuple_element_t<I, ArgTypes>>(), ...);
    }

    template<typename System, typename Component>
    void setComponentSignature()
    {
        size_t componentIndex = typeTag.get<Component>();
        size_t systemIndex = typeTag.get<System>();
        signatures[systemIndex].set(componentIndex);
    }

private:
    std::array<Signature, sizeof...(SystemTypes)> signatures;
    TypeTag typeTag;
};
