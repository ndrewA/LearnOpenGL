#pragma once

#include "Event.h"

class WindowEvent : public Event 
{
public: 
	EVENT_CATEGORY_FUNCTION(Window)
};

class WindowResizeEvent : public WindowEvent 
{
public: 
	WindowResizeEvent(const int width, const int height) 
		: width(width), height(height) { }

	const int getWidth() const { return width; }
	const int getHeight() const { return height; }

	EVENT_TYPE_FUNCTION(WindowResize)

private:
	const int width, height;
};

class WindowCloseEvent : public WindowEvent
{
public:
	EVENT_TYPE_FUNCTION(WindowClose)
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

class WindowCursorEnterEvent : public WindowEvent
{
public:
	EVENT_TYPE_FUNCTION(WindowCursorEnter)
};

class WindowCursorLeaveEvent : public WindowEvent
{
public:
	EVENT_TYPE_FUNCTION(WindowCursorLeave)
};
