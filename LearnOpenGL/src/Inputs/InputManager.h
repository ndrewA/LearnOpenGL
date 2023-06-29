#pragma once

#include "MouseState.h"
#include "KeyboardState.h"
#include "CharState.h"

class InputManager
{
public:
	InputManager(EventManager& eventManager);

	bool isKeyPressed(const int keyCode) const { return keyboardState.isKeyPressed(keyCode); }
	bool isKeyRepeated(const int keyCode) const { return keyboardState.isKeyRepeated(keyCode); }
	bool isKeyReleased(const int keyCode) const { return keyboardState.isKeyReleased(keyCode); }
	KeyboardState::ButtonState getButtonState(const int keyCode) const { return keyboardState.getKeyState(keyCode); }

	std::string getCharsDown() const { return charState.getCharsDown(); }
	void clearCharState() { charState.clear(); }

	bool isButtonPressed(const int keyCode) const { return mouseState.isButtonDown(keyCode); }
	MouseState::Position getMousePosition() const { return mouseState.getPosition(); }

	void setTextInputMode(const bool enabled) { textInputMode = enabled; }
	
private:
	template<typename EventType>
	void registerListener(EventManager& eventManager, void (InputManager::* handler)(const EventType&))
	{
		eventManager.registerListenerFor<EventType>
			([this, handler](const EventType& event) { (this->*handler)(event); });
	}

	void handleKeyboardPressEvent(const KeyboardPressEvent& event);
	void handleKeyboardRepeatEvent(const KeyboardRepeatEvent& event);
	void handleKeyboardReleaseEvent(const KeyboardReleaseEvent& event);
	void handleCharPressEvent(const CharPressEvent& event);
	void handleMouseButtonPressEvent(const MousePressEvent& event);
	void handleMouseButtonReleaseEvent(const MouseReleaseEvent& event);
	void handleMouseMoveEvent(const MouseMoveEvent& event);

private:
	KeyboardState keyboardState;
	CharState charState;
	MouseState mouseState;

	bool textInputMode = false;
};