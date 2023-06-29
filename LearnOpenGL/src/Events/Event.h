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
	const EventCategory category;
	const EventType type;
	const std::string name;
};

class Event
{
public:
	virtual ~Event() = default;

	bool handle() { handled = true; }
	bool isHandled() const { return handled; }

	EventCategory getCategory() const { return getDescription().category; }
	EventType getType()			const { return getDescription().type;     }
	std::string getTypeName()	const { return getDescription().name;     }

	virtual EventDescription getDescription() const = 0;

private:
	bool handled = false;
};									

class NoneEvent : public Event
{
public:
	EventDescription getDescription() const override { return { EventCategory::None, EventType::None, "None" }; }
};