#pragma once

struct TypeTag
{
    size_t counter = 0;

    template<typename T>
    static size_t get()
    {
        static size_t value = counter++;
        return value;
    }
};