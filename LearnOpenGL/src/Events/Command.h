#pragma once

#include <iostream>

class Command
{
public:
	virtual ~Command() = default;
	virtual void execute() = 0;
};

class KeyPressCommand : public Command
{
public:
    void execute() override
    {
        std::cout << "key\n";
        // Perform the desired action for key press event
    }
};

class MouseMoveCommand : public Command
{
public:
    void execute() override
    {
        std::cout << "mouse\n";
        // Perform the desired action for mouse move event
    }
};