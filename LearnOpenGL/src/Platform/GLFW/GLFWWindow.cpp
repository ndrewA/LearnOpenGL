#include "GLFWWindow.h"

#include <stdexcept>
#include <assert.h>

#include <GLFW/glfw3.h>

GLFWWindow::GLFWWindow(unsigned int height, unsigned int width, const std::string& name, EventManager& eventManager)
	: height(height), width(width), name(name)
{
	create();
	setupCallBacks(eventManager);
}

void GLFWWindow::create()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	windowHandle = glfwCreateWindow(height, width, name.c_str(), nullptr, nullptr);
	
	assert(windowHandle != nullptr && "Window not created!");
	
	renderingContext = std::make_unique<GLFWRenderingContext>(windowHandle);
	renderingContext->init();
}

void GLFWWindow::setupCallBacks(EventManager& eventManager)
{
	glfwSetWindowUserPointer(windowHandle, &eventManager);
	
	setupKeyboardCallBacks(eventManager);
	setupMouseCallBacks(eventManager);
	setupWindowCallBacks(eventManager);
}

void GLFWWindow::setupKeyboardCallBacks(EventManager& eventManager)
{
	glfwSetKeyCallback(windowHandle, [](GLFWwindow* window, int keyCode, int scancode, int action, int mods)
	{
		auto eventManager = static_cast<EventManager*>(glfwGetWindowUserPointer(window));
		switch (action)
		{
			case GLFW_PRESS:
				eventManager->pushEvent<KeyboardPressEvent>(keyCode, scancode, mods);
				break;
			case GLFW_REPEAT:
				eventManager->pushEvent<KeyboardPressEvent>(keyCode, scancode, mods);
				break;
			case GLFW_RELEASE:
				eventManager->pushEvent<KeyboardReleaseEvent>(keyCode, scancode, mods);
				break;
		}
	});

	glfwSetCharCallback(windowHandle, [](GLFWwindow* window, unsigned int codePoint)
	{
		auto eventManager = static_cast<EventManager*>(glfwGetWindowUserPointer(window));
		eventManager->pushEvent<CharPressEvent>(codePoint);
	});
}

void GLFWWindow::setupMouseCallBacks(EventManager& eventManager)
{
	glfwSetMouseButtonCallback(windowHandle, [](GLFWwindow* window, int button, int action, int mods)
	{
		auto eventManager = static_cast<EventManager*>(glfwGetWindowUserPointer(window));
		switch (action)
		{
			case GLFW_PRESS:
				eventManager->pushEvent<MousePressEvent>(button, mods);
				break;
			case GLFW_RELEASE:
				eventManager->pushEvent<MouseReleaseEvent>(button, mods);
				break;
		}
	});

	glfwSetScrollCallback(windowHandle, [](GLFWwindow* window, double xoffset, double yoffset)
	{
		auto eventManager = static_cast<EventManager*>(glfwGetWindowUserPointer(window));
		eventManager->pushEvent<MouseScrollEvent>(xoffset, yoffset);
	});

	glfwSetCursorPosCallback(windowHandle, [](GLFWwindow* window, double xpos, double ypos)
	{
		auto eventManager = static_cast<EventManager*>(glfwGetWindowUserPointer(window));
		eventManager->pushEvent<MouseMoveEvent>(xpos, ypos);
	});

	glfwSetFramebufferSizeCallback(windowHandle, [](GLFWwindow* window, int width, int height) {
		auto eventManager = static_cast<EventManager*>(glfwGetWindowUserPointer(window));
		eventManager->pushEvent<WindowResizeEvent>(width, height); //////////////////////////// TODO: renderer->onWindowResize(width, height); glViewport(0, 0, width, height);
	});
}

void GLFWWindow::setupWindowCallBacks(EventManager& eventManager)
{
	glfwSetWindowSizeCallback(windowHandle, [](GLFWwindow* window, int width, int height)
	{
		auto eventManager = static_cast<EventManager*>(glfwGetWindowUserPointer(window));
		eventManager->pushEvent<WindowResizeEvent>(width, height);
	});

	glfwSetWindowCloseCallback(windowHandle, [](GLFWwindow* window)
	{
		auto eventManager = static_cast<EventManager*>(glfwGetWindowUserPointer(window));
		eventManager->pushEvent<WindowCloseEvent>();
	});

	glfwSetWindowFocusCallback(windowHandle, [](GLFWwindow* window, int focused)
	{
		auto eventManager = static_cast<EventManager*>(glfwGetWindowUserPointer(window));
		focused ? 
			eventManager->pushEvent<WindowGainedFocusEvent>()
			: eventManager->pushEvent<WindowLostFocusEvent>();
	});

	glfwSetCursorEnterCallback(windowHandle, [](GLFWwindow* window, int entered)
	{
		auto eventManager = static_cast<EventManager*>(glfwGetWindowUserPointer(window));
		entered ? 
			eventManager->pushEvent<WindowCursorEnterEvent>()
			: eventManager->pushEvent<WindowCursorLeaveEvent>();
	});
}

void GLFWWindow::close()
{
	glfwDestroyWindow(windowHandle);
	glfwTerminate();
}

void GLFWWindow::update()
{
	glfwPollEvents();
	swapBuffers();
}

void GLFWWindow::hideCursor()
{
	glfwSetInputMode(windowHandle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void GLFWWindow::swapBuffers()
{
	renderingContext->swapBuffers();
}