#include "GLFWWindow.h"

#include <iostream>
#include <stdexcept>

#include <GLFW/glfw3.h>

GLFWWindow::GLFWWindow(const uint32_t height, const uint32_t width, const std::string& name, std::shared_ptr<EventManager>& eventManager)
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
	if (windowHandle == nullptr) {
		close();
		throw std::runtime_error("Failed to create GLFW window!");
	}
	renderingContext = std::make_unique<GLFWRenderingContext>(windowHandle);
	renderingContext->init();
}

void GLFWWindow::setupCallBacks(std::shared_ptr<EventManager>& eventManager)
{
	glfwSetWindowUserPointer(windowHandle, eventManager.get());
	
	setupKeyboardCallBacks(eventManager);
	setupMouseCallBacks(eventManager);
	setupWindowCallBacks(eventManager);
}

void GLFWWindow::setupKeyboardCallBacks(std::shared_ptr<EventManager>& eventManager)
{
	glfwSetKeyCallback(windowHandle, [](GLFWwindow* window, int keyCode, int scancode, int action, int mods)
	{
		auto eventManager = static_cast<EventManager*>(glfwGetWindowUserPointer(window));
		switch (action)
		{
			case GLFW_PRESS:
				eventManager->addEvent(std::make_shared<KeyboardPressEvent>(keyCode, scancode, mods));
				break;
			case GLFW_REPEAT:
				eventManager->addEvent(std::make_shared<KeyboardPressEvent>(keyCode, scancode, mods));
				break;
			case GLFW_RELEASE:
				eventManager->addEvent(std::make_shared<KeyboardReleaseEvent>(keyCode, scancode, mods));
				break;
		}
	});

	glfwSetCharCallback(windowHandle, [](GLFWwindow* window, unsigned int codePoint)
	{
		auto eventManager = static_cast<EventManager*>(glfwGetWindowUserPointer(window));
		eventManager->addEvent(std::make_shared<CharPressEvent>(codePoint));
	});
}

void GLFWWindow::setupMouseCallBacks(std::shared_ptr<EventManager>& eventManager)
{
	glfwSetMouseButtonCallback(windowHandle, [](GLFWwindow* window, int button, int action, int mods)
	{
		auto eventManager = static_cast<EventManager*>(glfwGetWindowUserPointer(window));
		switch (action)
		{
			case GLFW_PRESS:
				eventManager->addEvent(std::make_shared<MousePressEvent>(button, mods));
				break;
			case GLFW_RELEASE:
				eventManager->addEvent(std::make_shared<MouseReleaseEvent>(button, mods));
				break;
		}
	});

	glfwSetScrollCallback(windowHandle, [](GLFWwindow* window, double xoffset, double yoffset)
	{
		auto eventManager = static_cast<EventManager*>(glfwGetWindowUserPointer(window));
		eventManager->addEvent(std::make_shared<MouseScrollEvent>(xoffset, yoffset));
	});

	glfwSetCursorPosCallback(windowHandle, [](GLFWwindow* window, double xpos, double ypos)
	{
		auto eventManager = static_cast<EventManager*>(glfwGetWindowUserPointer(window));
		eventManager->addEvent(std::make_shared<MouseMoveEvent>(xpos, ypos));
	});

	glfwSetFramebufferSizeCallback(windowHandle, [](GLFWwindow* window, int width, int height) {
		auto eventManager = static_cast<EventManager*>(glfwGetWindowUserPointer(window));
		eventManager->addEvent(std::make_shared<WindowResizeEvent>(width, height)); //////////////////////////// TODO: renderer->onWindowResize(width, height); glViewport(0, 0, width, height);
	});
}

void GLFWWindow::setupWindowCallBacks(std::shared_ptr<EventManager>& eventManager)
{
	glfwSetWindowSizeCallback(windowHandle, [](GLFWwindow* window, int width, int height)
	{
		auto eventManager = static_cast<EventManager*>(glfwGetWindowUserPointer(window));
		eventManager->addEvent(std::make_shared<WindowResizeEvent>(width, height));
	});

	glfwSetWindowCloseCallback(windowHandle, [](GLFWwindow* window)
	{
		auto eventManager = static_cast<EventManager*>(glfwGetWindowUserPointer(window));
		eventManager->addEvent(std::make_shared<WindowCloseEvent>());
	});

	glfwSetWindowFocusCallback(windowHandle, [](GLFWwindow* window, int focused)
	{
		auto eventManager = static_cast<EventManager*>(glfwGetWindowUserPointer(window));
		focused ? 
			eventManager->addEvent(std::make_shared<WindowGainedFocusEvent>())
			: eventManager->addEvent(std::make_shared<WindowLostFocusEvent>());
	});

	glfwSetCursorEnterCallback(windowHandle, [](GLFWwindow* window, int entered)
	{
		auto eventManager = static_cast<EventManager*>(glfwGetWindowUserPointer(window));
		entered ? 
			eventManager->addEvent(std::make_shared<WindowCursorEnterEvent>())
			: eventManager->addEvent(std::make_shared<WindowCursorLeaveEvent>());
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

