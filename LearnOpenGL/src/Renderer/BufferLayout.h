#pragma once

#include <string>
#include <vector>

#ifdef USING_OPENGL
    #define BACKEND_TYPE unsigned int
#else 
    #error "No SDK macro defined!"
#endif

enum class ElementType
{
    None = 0,
    Float, Float2, Float3, Float4,
    Mat3, Mat4,
    Int, Int2, Int3, Int4,
    Bool,
};

class BufferLayout
{
public:
    struct LayoutElement
    {
        std::string name;
        ElementType type;
        bool normalized = false;
        unsigned int count;
        unsigned int size;
        size_t offset;
    };

public:
    BufferLayout(const std::initializer_list<LayoutElement>& elements)
        : elements(elements) { calculateOffsetsAndStride(); }
    BufferLayout(const std::vector<LayoutElement>& elements)
        : elements(elements) {  calculateOffsetsAndStride(); }

    virtual BACKEND_TYPE getBackendDataType(const ElementType type) const = 0;

    const std::vector<LayoutElement>& getElements() const { return elements; }
    size_t getStride() const { return stride; }

    auto begin()         { return elements.begin();  }
    auto begin() const   { return elements.begin();  }
    auto end()           { return elements.end();    }
    auto end()   const   { return elements.end();    }

    void calculateOffsetsAndStride();
    unsigned int getSizeFromType(const ElementType type) const;
    unsigned int getCountFromType(const ElementType type) const;

private:
    std::vector<LayoutElement> elements;
    size_t stride;
};