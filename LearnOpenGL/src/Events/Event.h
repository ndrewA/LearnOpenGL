#pragma once

#include <string>

enum class EventCategory
{
	None,
	Window,
	Mouse,
	Keyboard,
	Application
};

enum class EventType
{
	None,
	WindowResize, WindowLostFocus, WindowGainedFocus,
	MouseMove, MousePress, MouseRelease, MouseScroll,
	KeyboardPress, KeyboardRelease, KeyPress
};

class Event
{
public:
	virtual ~Event() = default;

	virtual const EventType getType() const = 0;
};									

#define EVENT_TYPE_FUNCTION(type)																			\
static const EventType getStaticType() { return EventType::##type; }										\
const EventType getType() const override { return EventType::##type; }										\
const std::string getTypeName() { return #type; }

#define EVENT_CATEGORY_FUNCTION(category)																	\
static const EventCategory getCategory() { return EventCategory::##category; }								\
virtual const EventType getType() const = 0;