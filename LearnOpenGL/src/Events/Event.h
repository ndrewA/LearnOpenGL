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

	bool handle() { handeled = true; }
	bool isHandeled() const { return handeled; }

	void addOrigin(const std::string& origin) { this->origin = origin; }

	EventCategory getCategory() const { return getDescription().category; }
	EventType getType()			const { return getDescription().type;     }
	std::string getTypeName()	const { return getDescription().name;     }
	std::string getOrigin()		const { return origin; }

	virtual EventDescription getDescription() const = 0;

private:
	bool handeled = false;
	std::string origin;
};									

class NoneEvent : public Event
{
public:
	EventDescription getDescription() const override { return { EventCategory::None ,EventType::None, "None" }; }
};