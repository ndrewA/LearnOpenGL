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
	MouseMotionEvent(const double mouseX, const double mouseY)
		: mouseX(mouseX), mouseY(mouseY) { }

private:
	const double mouseX, mouseY;
};

class MouseMoveEvent : public MouseMotionEvent
{
public:
	MouseMoveEvent(const double mouseX, const double mouseY)
		: MouseMotionEvent(mouseX, mouseY) { }

	virtual ~MouseMoveEvent() = default;
	EventDescription getDescription() const override { return { EventType::MouseMove, "MouseMove" }; }
};

class MouseScrollEvent : public MouseMotionEvent
{
public:
	MouseScrollEvent(const double mouseX, const double mouseY)
		: MouseMotionEvent(mouseX, mouseY) { }

	virtual ~MouseScrollEvent() = default;
	EventDescription getDescription() const override { return { EventType::MouseScroll, "MouseScroll" }; }
};

// ===================== BUTTON UPCOMING ==============================

class MouseButtonEvent : public MouseEvent
{
protected:
	MouseButtonEvent(const int button, const int mods)
		: button(button), mods(mods) { }

public:
	int getButton() const { return button; }
	int getMods() const { return mods; }

	virtual ~MouseButtonEvent() = default;
	EventDescription getDescription() const override = 0;

private:
	const int button, mods;
};

class MousePressEvent : public MouseButtonEvent
{
public: 
	MousePressEvent(const int button, const int mods)
		: MouseButtonEvent(button, mods) { }

	virtual ~MousePressEvent() = default;
	EventDescription getDescription() const override { return { EventType::MousePress, "MousePress" }; }
};

class MouseReleaseEvent : public MouseButtonEvent
{
public: 
	MouseReleaseEvent(const int button, const int mods)
		: MouseButtonEvent(button, mods) { }

	virtual ~MouseReleaseEvent() = default;
	EventDescription getDescription() const override { return { EventType::MouseRelease, "MouseRelease" }; }
};
