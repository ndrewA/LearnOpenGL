#pragma once

#include "Event.h"

class MouseEvent : public Event 
{
public:
	virtual ~MouseEvent() = default;
	EventDescription getDescription() const override = 0;
};

// ===================== MOTION UPCOMING ==============================

class MouseMotionEvent : public MouseEvent
{
public:
	double getMouseX() const { return mouseX; }
	double getMouseY() const { return mouseY; }

	virtual ~MouseMotionEvent() = default;
	EventDescription getDescription() const override = 0;

protected:
	MouseMotionEvent(double mouseX, double mouseY)
		: mouseX(mouseX), mouseY(mouseY) { }

private:
	double mouseX, mouseY;
};

class MouseMoveEvent : public MouseMotionEvent
{
public:
	MouseMoveEvent(double mouseX, double mouseY)
		: MouseMotionEvent(mouseX, mouseY) { }

	virtual ~MouseMoveEvent() = default;
	EventDescription getDescription() const override 
		{ return { EventCategory::Mouse, EventType::MouseMove, "MouseMove" }; }
};

class MouseScrollEvent : public MouseMotionEvent
{
public:
	MouseScrollEvent(double mouseX, double mouseY)
		: MouseMotionEvent(mouseX, mouseY) { }

	virtual ~MouseScrollEvent() = default;
	EventDescription getDescription() const override 
		{ return { EventCategory::Mouse, EventType::MouseScroll, "MouseScroll" }; }
};

// ===================== BUTTON UPCOMING ==============================

class MouseButtonEvent : public MouseEvent
{
protected:
	MouseButtonEvent(int button, int mods)
		: button(button), mods(mods) { }

public:
	int getButton() const { return button; }
	int getMods() const { return mods; }

	virtual ~MouseButtonEvent() = default;
	EventDescription getDescription() const override = 0;

private:
	int button, mods;
};

class MousePressEvent : public MouseButtonEvent
{
public: 
	MousePressEvent(int button, int mods)
		: MouseButtonEvent(button, mods) { }

	virtual ~MousePressEvent() = default;
	EventDescription getDescription() const override 
		{ return { EventCategory::Mouse, EventType::MousePress, "MousePress" }; }
};

class MouseReleaseEvent : public MouseButtonEvent
{
public: 
	MouseReleaseEvent(int button, int mods)
		: MouseButtonEvent(button, mods) { }

	virtual ~MouseReleaseEvent() = default;
	EventDescription getDescription() const override 
		{ return { EventCategory::Mouse, EventType::MouseRelease, "MouseRelease" }; }
};
