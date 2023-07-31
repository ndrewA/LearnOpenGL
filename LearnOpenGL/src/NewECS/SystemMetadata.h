#pragma once

#include <array>
#include <bitset>

#include "TypeTag.h"
#include "HasUpdate.h"
#include "ComponentCount.h"
#include "Signature.h"

template <HasUpdate... SystemTypes>
class SystemMetadata
{
    static constexpr size_t COMPONENT_COUNT = ComponentCount<SystemTypes...>;
    using SignatureTuple = std::tuple<SystemSignature<SystemTypes, COMPONENT_COUNT>...>;

public:
    SystemMetadata()
    {
        (setSignature<SystemTypes>(), ...);
    }

    template <typename SystemType>
    bool matches(const EntitySignature<COMPONENT_COUNT>& entitySignature) const
    {
        auto& systemSignature = std::get<SystemSignature<SystemType, COMPONENT_COUNT>>(signatures);
        return (systemSignature & entitySignature) == systemSignature;
    }

private:
    template<typename System>
    void setSignature()
    {
        using ArgTypes = typename FunctionTraits<decltype(&System::update)>::ArgTypes;
        setSignatureHelper<System>(std::make_index_sequence<std::tuple_size_v<ArgTypes>>{});
    }

    template<typename System, size_t... I>
    void setSignatureHelper(std::index_sequence<I...>)
    {
        (setComponentSignature<System, std::tuple_element_t<I, FunctionTraits_t<decltype(&System::update)>>>(), ...);
    }

    template<typename System, typename Component>
    void setComponentSignature()
    {
        size_t componentIndex = componentTypeTag.get<Component>();
        auto& systemSignature = std::get<SystemSignature<System, COMPONENT_COUNT>>(signatures);
        systemSignature.set(componentIndex);
    }

private:
    SignatureTuple signatures;
    TypeTag componentTypeTag;
};

