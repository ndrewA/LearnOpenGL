#include "GLFWRenderingContext.h"

#include <iostream>
#include  <stdexcept>
#include <assert.h>

#include <glad/glad.h>

GLFWRenderingContext::GLFWRenderingContext(GLFWwindow* windowHandle)
	: windowHandle(windowHandle)
{
}

void GLFWRenderingContext::init()
{
	glfwMakeContextCurrent(windowHandle);
	int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	assert(status && "Rendering context not initalized!");
}

void GLFWRenderingContext::swapBuffers()
{
	glfwSwapBuffers(windowHandle);
}
