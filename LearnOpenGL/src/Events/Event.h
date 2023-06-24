#pragma once

#include <string>

#define EVENT_TYPE_FUNCTION(type)																			\
static const EventType getStaticType() { return EventType::##type; }										\
virtual const EventType getType() const override { return EventType::##type; }								\
virtual const std::string getTypeName() const override { return #type; }

#define EVENT_CATEGORY_FUNCTION(category)																	\
virtual ~category##Event() override = default;																\
virtual const EventCategory getCategory() const override { return EventCategory::##category; }				\
virtual const EventType getType() const override{ return EventType::None; }

enum class EventCategory
{
	None,
	Input,
	Window,
	Mouse,
	Keyboard,
	Application,
};

enum class EventType
{
	None,
	WindowResize, WindowLostFocus, WindowGainedFocus, 
	WindowClose, WindowCursorEnter, WindowCursorLeave,
	MouseMove, MousePress, MouseRelease, MouseScroll,
	KeyboardPress, KeyboardRepeat, KeyboardRelease, CharPress,
};

class Event
{
public:
	virtual ~Event() = default;

	bool isHandeled() const { return handeled; }
	bool handle() { handeled = true; }

	virtual const EventCategory getCategory() const = 0;
	virtual const EventType getType() const = 0;
	virtual const std::string getTypeName() const = 0;

private:
	bool handeled = false;
};									

class NoneEvent : public Event
{
	const EventCategory getCategory() const override { return EventCategory::None; }
	EVENT_TYPE_FUNCTION(None)
};