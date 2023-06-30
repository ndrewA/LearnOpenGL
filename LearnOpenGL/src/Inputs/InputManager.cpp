#include "InputManager.h"

#include <iostream>
InputManager::InputManager(EventManager& eventManager)
{
    registerListener(eventManager, &InputManager::handleKeyboardPressEvent);
    registerListener(eventManager, &InputManager::handleKeyboardRepeatEvent);
    registerListener(eventManager, &InputManager::handleKeyboardReleaseEvent);
    registerListener(eventManager, &InputManager::handleCharPressEvent);
    registerListener(eventManager, &InputManager::handleMouseButtonPressEvent);
    registerListener(eventManager, &InputManager::handleMouseButtonReleaseEvent);
    registerListener(eventManager, &InputManager::handleMouseMoveEvent);
}

void InputManager::handleKeyboardPressEvent(const KeyboardPressEvent& event)
{
    keyboardState.keyPress(event.getKeyCode());
}

void InputManager::handleKeyboardRepeatEvent(const KeyboardRepeatEvent& event)
{
    keyboardState.keyRepeat(event.getKeyCode());
}

void InputManager::handleKeyboardReleaseEvent(const KeyboardReleaseEvent& event)
{
    keyboardState.keyRelease(event.getKeyCode());
}

void InputManager::handleCharPressEvent(const CharPressEvent& event)
{
    std::cout << (char)event.getCodePoint();
    if (textInputMode)
        charState.charDown(event.getCodePoint());
}

void InputManager::handleMouseButtonPressEvent(const MousePressEvent& event)
{
    mouseState.keyDown(event.getButton());
}

void InputManager::handleMouseButtonReleaseEvent(const MouseReleaseEvent& event)
{
    mouseState.keyRelease(event.getButton());
}

void InputManager::handleMouseMoveEvent(const MouseMoveEvent& event)
{
    mouseState.setPosition({ event.getMouseX(), event.getMouseY() });
}
