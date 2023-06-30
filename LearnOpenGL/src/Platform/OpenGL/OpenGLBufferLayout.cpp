#include "OpenGLBufferLayout.h"

#include <stdexcept>

#include <glad/glad.h>

BACKEND_TYPE OpenGLBufferLayout::getBackendDataType(ElementType type) const
{
    switch (type)
    {
        case ElementType::Float:
        case ElementType::Float2:
        case ElementType::Float3:
        case ElementType::Float4:
        case ElementType::Mat3:
        case ElementType::Mat4:
            return GL_FLOAT;
        case ElementType::Int:
        case ElementType::Int2:
        case ElementType::Int3:
        case ElementType::Int4:
            return GL_INT;
        case ElementType::Bool:
            return GL_BOOL;
        default:
            throw std::runtime_error("ElementType::None does not correspond to an OpenGL type");
    }
}
