#pragma once

#include "Event.h"

class WindowEvent : public Event 
{
public: 
	virtual ~WindowEvent() = default;

	EVENT_CATEGORY_FUNCTION(Window)
};

class WindowResizeEvent : public WindowEvent 
{
public: 
	EVENT_TYPE_FUNCTION(WindowResize)
};

class WindowLostFocusEvent : public WindowEvent 
{
public: 
	EVENT_TYPE_FUNCTION(WindowLostFocus)
};

class WindowGainedFocusEvent : public WindowEvent 
{
public: 
	EVENT_TYPE_FUNCTION(WindowGainedFocus)
};