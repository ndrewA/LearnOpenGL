#pragma once

#include <string>

#include "Window.h"
#include "GLFWRenderingContext.h"

class GLFWWindow : public Window
{
public:
    GLFWWindow(unsigned int height, unsigned int width, const std::string& name, EventManager& eventManager);
    ~GLFWWindow() override { close(); }

    void create() override;
    void close() override;
    void update() override;

    void hideCursor() override;

    int getWidth() const override { return width; }
    int getHeight() const override { return height; }
    std::string getName() const override { return name; }

private:
    void setupCallBacks(EventManager& eventManager);
    void setupKeyboardCallBacks(EventManager& eventManager);
    void setupMouseCallBacks(EventManager& eventManager);
    void setupWindowCallBacks(EventManager& eventManager);

private:
    GLFWwindow* windowHandle;

    int width, height;
    std::string name;

    std::unique_ptr<GLFWRenderingContext> renderingContext;
};