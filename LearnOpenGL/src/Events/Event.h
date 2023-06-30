#pragma once

#include <string>

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

struct EventDescription
{
	EventCategory category;
	EventType type;
	const char* name;
};

class Event
{
public:
	virtual ~Event() = default;

	EventCategory getCategory() const { return getDescription().category; }
	EventType getType()			const { return getDescription().type;     }
	const char* getTypeName()	const { return getDescription().name;     }

	virtual EventDescription getDescription() const = 0;
};									

class NoneEvent : public Event
{
public:
	EventDescription getDescription() const override { return { EventCategory::None, EventType::None, "None" }; }
};