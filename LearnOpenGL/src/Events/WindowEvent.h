#pragma once

#include "Event.h"

class WindowEvent : public Event 
{
public: 
	virtual ~WindowEvent() = default;
	EventDescription getDescription() const override = 0;
};

class WindowResizeEvent : public WindowEvent 
{
public: 
	WindowResizeEvent(const int width, const int height) 
		: width(width), height(height) { }

	virtual ~WindowResizeEvent() = default;
	EventDescription getDescription() const override 
		{ return { EventCategory::Window, EventType::WindowResize, "WindowResize" }; }

	int getWidth() const { return width; }
	int getHeight() const { return height; }

private:
	const int width, height;
};

class WindowCloseEvent : public WindowEvent
{
public:
	virtual ~WindowCloseEvent() = default;
	EventDescription getDescription() const override 
		{ return { EventCategory::Window, EventType::WindowClose, "WindowClose" }; }
};

class WindowLostFocusEvent : public WindowEvent 
{
public: 
	virtual ~WindowLostFocusEvent() = default;
	EventDescription getDescription() const override 
		{ return { EventCategory::Window, EventType::WindowLostFocus, "WindowLostFocus" }; }
};

class WindowGainedFocusEvent : public WindowEvent 
{
public: 
	virtual ~WindowGainedFocusEvent() = default;
	EventDescription getDescription() const override 
		{ return { EventCategory::Window, EventType::WindowGainedFocus, "WindowGainedFocus" }; }
};

class WindowCursorEnterEvent : public WindowEvent
{
public:
	virtual ~WindowCursorEnterEvent() = default;
	EventDescription getDescription() const override 
		{ return { EventCategory::Window, EventType::WindowCursorEnter, "WindowCursorEnter" }; }
};

class WindowCursorLeaveEvent : public WindowEvent
{
public:
	virtual ~WindowCursorLeaveEvent() = default;
	EventDescription getDescription() const override 
		{ return { EventCategory::Window, EventType::WindowCursorLeave, "WindowCursorLeave" }; }
};
