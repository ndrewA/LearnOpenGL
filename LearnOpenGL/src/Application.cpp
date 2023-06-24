#include "Application.h"

Application::Application()
{
	start();
}

void Application::start()
{
	window = std::make_unique<GLFWWindow>(1920, 1080, "App", eventManager);
	window->hideCursor();
	layerStack = std::make_unique<LayerStack>();
}

void Application::run()
{
	while (!shouldClose) {

	}
}

void Application::stop()
{
}

void Application::onEvent()
{
}
