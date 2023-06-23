#include "GLFWRenderingContext.h"

#include <iostream>
#include  <stdexcept>

#include <glad/glad.h>

GLFWRenderingContext::GLFWRenderingContext(GLFWwindow* windowHandle)
	: windowHandle(windowHandle)
{
}

void GLFWRenderingContext::init()
{
	glfwMakeContextCurrent(windowHandle);
	int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	if (!status) 
		throw std::runtime_error("Rendering context failed to initialize!");
}

void GLFWRenderingContext::swapBuffers()
{
	glfwSwapBuffers(windowHandle);
}
