#pragma once

#include <string>

#include "Events/EventManager.h"

class Window 
{
public:
    virtual ~Window() = default;

    virtual void create() = 0;
    virtual void close() = 0;
    virtual void update() = 0;

    virtual void hideCursor() = 0;

    virtual int getWidth() const = 0;
    virtual int getHeight() const = 0;
    virtual std::string getName() const = 0;
};