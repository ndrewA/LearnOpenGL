#include "Application.h"

#include "Timer.h"

Application::Application()
{
	start();
}

void Application::start()
{
	window = std::make_unique<GLFWWindow>(1920, 1080, "App", eventManager);
	eventManager.registerPermanentListenerFor<WindowCloseEvent>([this](const WindowCloseEvent& event) { return onEvent(event); });
}

void Application::run()
{
	Timer timer;

	while (isRunning) {
		eventManager.publishEvents();
		ecsManager.updateSystems(timer.mark());
		window->update();
	}
}

void Application::stop()
{
}

bool Application::onEvent(const WindowCloseEvent& event)
{
	isRunning = false;
	return true;
}
