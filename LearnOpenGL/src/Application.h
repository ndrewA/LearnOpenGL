#pragma once

#include "Events/EventManager.h"
#include "LayerStack.h"
#include "Platform/GLFW/GLFWWindow.h"
#include "ECS/ECSManager.h"

class Application
{
public:
	Application();

	void start();
	void run();
	void stop();

	bool onEvent(const WindowCloseEvent& event);
	
private:
	EventManager eventManager;
	ECSManager ecsManager;
	LayerStack layerStack;
	std::unique_ptr<Window> window;
	
	bool isRunning = true;
};

