#pragma once

#include "Event.h"

#include <Stdint.h>

class KeyboardEvent : public Event
{
protected:
	KeyboardEvent(int keyCode, int scancode, int mods)
		: keyCode(keyCode), scancode(scancode), mods(mods) { }

public:
	virtual ~KeyboardEvent() = default;
	EventDescription getDescription() const override = 0;

	int getKeyCode() const { return keyCode; }
	int getScanCode() const { return scancode; }
	int getMods() const { return mods; }

private:
	int keyCode;
	int scancode;
	int mods;
};

class KeyboardPressEvent : public KeyboardEvent
{
public:
	KeyboardPressEvent(int keyCode, int scancode, int mods)
		: KeyboardEvent(keyCode, scancode, mods) { }

	EventDescription getDescription() const override 
		{ return { EventCategory::Keyboard, EventType::KeyboardPress, "KeyboardPress"}; }
};

class KeyboardRepeatEvent : public KeyboardEvent
{
	KeyboardRepeatEvent(int keyCode, int scancode, int mods)
		: KeyboardEvent(keyCode, scancode, mods) { }

	EventDescription getDescription() const override 
		{ return { EventCategory::Keyboard, EventType::KeyboardRepeat, "KeyboardRepeat" }; }
};

class KeyboardReleaseEvent : public KeyboardEvent
{
public:
	KeyboardReleaseEvent(int keyCode, int scancode, int mods)
		: KeyboardEvent(keyCode, scancode, mods) { }

	EventDescription getDescription() const override 
		{ return { EventCategory::Keyboard, EventType::KeyboardRelease, "KeyboardRelease" }; }

};

class CharPressEvent : public Event
{
public:
	CharPressEvent(int codePoint)
		: codePoint(codePoint) { }

	int getCodePoint() const { return codePoint; }

	EventDescription getDescription() const override 
		{ return { EventCategory::Keyboard, EventType::CharPress, "CharPress" }; }

private:
	int codePoint;
};