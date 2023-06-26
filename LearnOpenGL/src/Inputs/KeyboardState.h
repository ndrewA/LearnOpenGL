#pragma once

#include <unordered_map>

#include "Events/EventManager.h"

class KeyboardState
{
public:
	enum class ButtonState
	{
		Pressed,
		Repeat,
		Released
	};

	void keyPress(const int keyCode) { keyStates[keyCode] = ButtonState::Pressed; }
	void keyRepeat(const int keyCode) { keyStates[keyCode] = ButtonState::Repeat; }
	void keyRelease(const int keyCode) { keyStates[keyCode] = ButtonState::Released;  }

	ButtonState getKeyState(const int keyCode) const { return keyStates[keyCode]; }
	bool isKeyPressed(const int keyCode) const { return keyStates[keyCode] == ButtonState::Pressed; }
	bool isKeyRepeated(const int keyCode) const { return keyStates[keyCode] == ButtonState::Repeat; }
	bool isKeyReleased(const int keyCode) const { return keyStates[keyCode] == ButtonState::Released; }

private:
	mutable std::unordered_map<int, ButtonState> keyStates;
};
