#pragma once

class RenderingContext
{
public:
	virtual ~RenderingContext() = default;

	virtual void init() = 0;
	virtual void swapBuffers() = 0;
};