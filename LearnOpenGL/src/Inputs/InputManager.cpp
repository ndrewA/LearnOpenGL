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

void InputManager::handleKeyboardPressEvent(const std::shared_ptr<KeyboardPressEvent>& event)
{
    keyboardState.keyPress(event->getKeyCode());
}

void InputManager::handleKeyboardRepeatEvent(const std::shared_ptr<KeyboardRepeatEvent>& event)
{
    keyboardState.keyRepeat(event->getKeyCode());
}

void InputManager::handleKeyboardReleaseEvent(const std::shared_ptr<KeyboardReleaseEvent>& event)
{
    keyboardState.keyRelease(event->getKeyCode());
}

void InputManager::handleCharPressEvent(const std::shared_ptr<CharPressEvent>& event)
{
    std::cout << (char)event->getCodePoint() << '\n';
    if(textInputMode)
        charState.charDown(event->getCodePoint());
}

void InputManager::handleMouseButtonPressEvent(const std::shared_ptr<MousePressEvent>& event)
{
    mouseState.keyDown(event->getButton());
}

void InputManager::handleMouseButtonReleaseEvent(const std::shared_ptr<MouseReleaseEvent>& event)
{
    mouseState.keyRelease(event->getButton());
}

void InputManager::handleMouseMoveEvent(const std::shared_ptr<MouseMoveEvent>& event)
{
    mouseState.setPosition({ event->getMouseX(), event->getMouseY() });
}
