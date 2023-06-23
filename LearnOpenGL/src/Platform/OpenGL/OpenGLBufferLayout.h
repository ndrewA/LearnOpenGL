#pragma once

#ifdef USING_OPENGL

#include "Generic/BufferLayout.h"

class OpenGLBufferLayout : public BufferLayout
{
public:
	OpenGLBufferLayout(const std::initializer_list<LayoutElement>& elements)
		: BufferLayout(elements) { }
	OpenGLBufferLayout(const std::vector<LayoutElement>& elements)
		: BufferLayout(elements) { }

	BACKEND_TYPE getBackendDataType(const ElementType type) const override;
};

#endif 