#pragma once

#include "Event.h"

class MouseEvent : public Event 
{
public:
	EVENT_CATEGORY_FUNCTION(Mouse)
};

class MouseMoveEvent : public MouseEvent 
{
public:
	MouseMoveEvent(double mouseX, double mouseY)
		: mouseX(mouseX), mouseY(mouseY) { }

	double getMouseX() const { return mouseX; }
	double getMouseY() const { return mouseY; }

	EVENT_TYPE_FUNCTION(MouseMove)

private:
	double mouseX, mouseY;
};

class MouseScrollEvent : public MouseEvent 
{
public:
	EVENT_TYPE_FUNCTION(MouseScroll)
};

class MousePressEvent : public MouseEvent 
{
public: 
	EVENT_TYPE_FUNCTION(MousePress)
};

class MouseReleaseEvent : public MouseEvent 
{
public: 
	EVENT_TYPE_FUNCTION(MouseRelease)
};
