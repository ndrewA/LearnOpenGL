#pragma once

#include "Event.h"

class MouseEvent : public Event 
{
public:
	virtual ~MouseEvent() = default;

	EVENT_CATEGORY_FUNCTION(Mouse)
};

class MouseMoveEvent : public MouseEvent 
{
public:
	EVENT_TYPE_FUNCTION(MouseMove)
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

class MouseScrollEvent : public MouseEvent 
{
public:
	EVENT_TYPE_FUNCTION(MouseScroll)
};