#pragma once

#include "Events/EventManager.hpp"
#include "LayerStack.h"
#include "Platform/GLFW/GLFWWindow.h"

class Application
{
	Application();

	void start();
	void run();
	void stop();

	void onEvent();

private:
	std::unique_ptr<Window> window;
	std::shared_ptr<EventManager> eventManager;
	std::unique_ptr<LayerStack> layerStack;
	
	bool shouldClose = false;
};

