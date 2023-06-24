#pragma once

#include <unordered_map>

#include "Events/EventManager.hpp"

enum class KeyState 
{ 
	Pressed, 
	Repeat, 
	Released 
};

class KeyboardState
{
public:
	void keyPress(const int keyCode) { keyStates[keyCode] = KeyState::Pressed; }
	void keyRepeat(const int keyCode) { keyStates[keyCode] = KeyState::Repeat; }
	void keyRelease(const int keyCode) { keyStates[keyCode] = KeyState::Released;  }

	KeyState getKeyState(const int keyCode) const { return keyStates[keyCode]; }
	bool isKeyPressed(const int keyCode) const { return keyStates[keyCode] == KeyState::Pressed; }
	bool isKeyRepeated(const int keyCode) const { return keyStates[keyCode] == KeyState::Repeat; }
	bool isKeyReleased(const int keyCode) const { return keyStates[keyCode] == KeyState::Released; }

private:
	mutable std::unordered_map<int, KeyState> keyStates;
};
