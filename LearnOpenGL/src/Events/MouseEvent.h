#pragma once

#include "Event.h"

class MouseEvent : public Event 
{
public:
	EVENT_CATEGORY_FUNCTION(Mouse)
};

// ===================== MOTION UPCOMING ==============================

class MouseMotionEvent : public MouseEvent
{
protected:
	MouseMotionEvent(const double mouseX, const double mouseY)
		: mouseX(mouseX), mouseY(mouseY) { }

public:
	const double getMouseX() const { return mouseX; }
	const double getMouseY() const { return mouseY; }

private:
	const double mouseX, mouseY;
};

class MouseMoveEvent : public MouseMotionEvent
{
public:
	MouseMoveEvent(const double mouseX, const double mouseY)
		: MouseMotionEvent(mouseX, mouseY) { }

	EVENT_TYPE_FUNCTION(MouseMove)
};

class MouseScrollEvent : public MouseMotionEvent
{
public:
	MouseScrollEvent(const double mouseX, const double mouseY)
		: MouseMotionEvent(mouseX, mouseY) { }

	EVENT_TYPE_FUNCTION(MouseScroll)
};

// ===================== BUTTON UPCOMING ==============================

class MouseButtonEvent : public MouseEvent
{
protected:
	MouseButtonEvent(const int button, const int mods)
		: button(button), mods(mods) { }

public:
	const int getButton() const { return button; }
	const int getMods() const { return mods; }

private:
	const int button, mods;
};

class MousePressEvent : public MouseButtonEvent
{
public: 
	MousePressEvent(const int button, const int mods)
		: MouseButtonEvent(button, mods) { }

	EVENT_TYPE_FUNCTION(MousePress)
};

class MouseReleaseEvent : public MouseButtonEvent
{
public: 
	MouseReleaseEvent(const int button, const int mods)
		: MouseButtonEvent(button, mods) { }

	EVENT_TYPE_FUNCTION(MouseRelease)
};
