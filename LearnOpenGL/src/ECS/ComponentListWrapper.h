#pragma once

#include "List/ListSorting.h"

class BaseListWrapper
{
public:
    virtual size_t getIdentifier() const = 0;
};

template <typename... ComponentTypes>
class ListWrapper : public BaseListWrapper {
public:
    size_t getIdentifier() const override {
        return Identifier<ComponentTypes...>::value;
    }
};