#pragma once

struct BaseTypeIndex
{
    inline static size_t typeCounter = 0;
};

template <typename ComponentType>
struct TypeIndex : BaseTypeIndex
{
    size_t index = typeCounter++;
};

//class TypeIndex
//{
//private:
//    size_t counter = 0;
//
//public:
//    template<typename T>
//    size_t get()
//    {
//        static size_t value = counter++;
//        return value;
//    }
//};