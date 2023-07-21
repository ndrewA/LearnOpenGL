#pragma once

struct TypeTag
{
    size_t counter = 0;

    template<typename T>
    size_t get()
    {
        static size_t value = counter++;
        return value;
    }
};