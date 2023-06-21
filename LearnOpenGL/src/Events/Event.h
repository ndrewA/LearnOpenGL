#pragma once

#include <string>

enum class EventCategory
{
	None,
	Input,
	Application,
	Window,
	Mouse,
	Keyboard,
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

	bool isHandeled() const { return handeled; }
	bool handle() { handeled = true; }

	virtual const EventType getType() const = 0;

private:
	bool handeled = false;
};									

#define EVENT_TYPE_FUNCTION(type)																			\
static const EventType getStaticType() { return EventType::##type; }										\
const EventType getType() const override { return EventType::##type; }										\
const std::string getTypeName() { return #type; }

#define EVENT_CATEGORY_FUNCTION(category)																	\
virtual ~category##Event() = default;																		\
static const EventCategory getCategory() { return EventCategory::##category; }								\
virtual const EventType getType() const = 0;

class NoneEvent : public Event
{
	static const EventCategory getCategory() { return EventCategory::None; }
	EVENT_TYPE_FUNCTION(None)
};