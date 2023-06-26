#include "BufferLayout.h"

#include <stdexcept>

void BufferLayout::calculateOffsetsAndStride()
{
    size_t offset = 0;
    stride = 0;
    for (auto& element : elements)
    {
        element.count = getCountFromType(element.type);
        element.size = getSizeFromType(element.type);
        element.offset = offset;
        offset += element.size;
    }
    stride = offset;
}

unsigned int BufferLayout::getSizeFromType(const ElementType type) const
{
    switch (type)
    {
        case ElementType::Float:    return          sizeof(float);
        case ElementType::Float2:   return 2 *      sizeof(float);
        case ElementType::Float3:   return 3 *      sizeof(float);
        case ElementType::Float4:   return 4 *      sizeof(float);
        case ElementType::Mat3:     return 3 * 3 *  sizeof(float);
        case ElementType::Mat4:     return 4 * 4 *  sizeof(float);
        case ElementType::Int:      return          sizeof(int);
        case ElementType::Int2:     return 2 *      sizeof(int);
        case ElementType::Int3:     return 3 *      sizeof(int);
        case ElementType::Int4:     return 4 *      sizeof(int);
        case ElementType::Bool:     return          sizeof(bool);
        case ElementType::None:     return 0;
        default: throw std::runtime_error("Unknown type!");
    }
}

unsigned int BufferLayout::getCountFromType(const ElementType type) const
{
    switch (type)
    {
    case ElementType::Float:    return 1;
    case ElementType::Float2:   return 2;
    case ElementType::Float3:   return 3;
    case ElementType::Float4:   return 4;
    case ElementType::Mat3:     return 3 * 3;
    case ElementType::Mat4:     return 4 * 4;
    case ElementType::Int:      return 1;
    case ElementType::Int2:     return 2;
    case ElementType::Int3:     return 3;
    case ElementType::Int4:     return 4;
    case ElementType::Bool:     return 1;
    case ElementType::None:     return 0;
    default: throw std::runtime_error("Unknown type!");
    }
}
