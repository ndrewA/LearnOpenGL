#pragma once

#include "Events/EventManager.h"

#include "MouseState.h"
#include "KeyboardState.h"
#include "CharState.h"

class InputManager
{
public:
	InputManager(EventManager& eventManager);

	bool isKeyPressed(int keyCode) const { return keyboardState.isKeyPressed(keyCode); }
	bool isKeyRepeated(int keyCode) const { return keyboardState.isKeyRepeated(keyCode); }
	bool isKeyReleased(int keyCode) const { return keyboardState.isKeyReleased(keyCode); }
	KeyboardState::ButtonState getButtonState(int keyCode) const { return keyboardState.getButtonState(keyCode); }

	std::string getCharsDown() const { return charState.getCharsDown(); }
	void clearCharState() { charState.clear(); }

	bool isButtonPressed(int keyCode) const { return mouseState.isButtonDown(keyCode); }
	MouseState::Position getMousePosition() const { return mouseState.getPosition(); }

	void setTextInputMode(bool enabled) { textInputMode = enabled; }
	
private:
	template<typename EventType>
	requires std::derived_from<EventType, Event>
	void registerListener(EventManager& eventManager, void (InputManager::* handler)(const EventType&))
	{
		auto test = eventManager.registerListenerFor<EventType>(
			[this, handler](const EventType& event) {
				(this->*handler)(event);
				return false;
			});
		keys.push_back(std::move(test));
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

	std::vector<EventListenerKey> keys;
};