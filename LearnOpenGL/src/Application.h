#pragma once

#include "Events/EventManager.h"
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
	EventManager eventManager;
	std::unique_ptr<LayerStack> layerStack;
	std::unique_ptr<Window> window;
	
	bool shouldClose = false;
};

