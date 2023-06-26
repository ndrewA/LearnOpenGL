#pragma once

#include "Renderer/Buffer.h"

class OpenGLElementBuffer : public ElementBuffer
{
public:
	OpenGLElementBuffer(const std::vector<unsigned int>& data);

	~OpenGLElementBuffer() override;

	void bind() const override;
	void unbind() const override;

private:
	unsigned int elementHandle;
};