#pragma once

#include <memory>

#include <GLFW/glfw3.h>

#include "Generic/RenderingContext.h"

class GLFWRenderingContext : public RenderingContext
{
public:
	GLFWRenderingContext(GLFWwindow* windowHandle);

	virtual void init() override;
	virtual void swapBuffers() override;

private:
	GLFWwindow* windowHandle;
};