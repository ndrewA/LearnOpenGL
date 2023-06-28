#pragma once

#include "Event.h"

#include <Stdint.h>

class KeyboardEvent : public Event
{
protected:
	KeyboardEvent(const int keyCode, const int scancode, const int mods)
		: keyCode(keyCode), scancode(scancode), mods(mods) { }

public:
	virtual ~KeyboardEvent() = default;
	EventDescription getDescription() const override = 0;

	int getKeyCode() const { return keyCode; }
	int getScanCode() const { return scancode; }
	int getMods() const { return mods; }

private:
	const int keyCode;
	const int scancode;
	const int mods;
};

class KeyboardPressEvent : public KeyboardEvent
{
public:
	KeyboardPressEvent(const int keyCode, const int scancode, const int mods)
		: KeyboardEvent(keyCode, scancode, mods) { }

	EventDescription getDescription() const override { return { EventType::KeyboardPress, "KeyboardPress"}; }
};

class KeyboardRepeatEvent : public KeyboardEvent
{
	KeyboardRepeatEvent(const int keyCode, const int scancode, const int mods)
		: KeyboardEvent(keyCode, scancode, mods) { }

	EventDescription getDescription() const override { return { EventType::KeyboardRepeat, "KeyboardRepeat" }; }
};

class KeyboardReleaseEvent : public KeyboardEvent
{
public:
	KeyboardReleaseEvent(const int keyCode, const int scancode, const int mods)
		: KeyboardEvent(keyCode, scancode, mods) { }

	EventDescription getDescription() const override { return { EventType::KeyboardRelease, "KeyboardRelease" }; }

};

class CharPressEvent : public Event
{
public:
	CharPressEvent(const int codePoint)
		: codePoint(codePoint) { }

	int getCodePoint() const { return codePoint; }

	EventDescription getDescription() const override { return { EventType::CharPress, "CharPress" }; }

private:
	const int codePoint;
};