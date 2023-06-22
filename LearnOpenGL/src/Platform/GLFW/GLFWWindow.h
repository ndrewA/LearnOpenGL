#pragma once

#include <string>

#include "Generic/Window.h"
#include "GLFWRenderingContext.h"

class GLFWWindow : public Window
{
public:
    GLFWWindow(const uint32_t height, const uint32_t width, const std::string& name, std::shared_ptr<EventManager>& eventManager);
    virtual ~GLFWWindow() { close(); }

    void create() override;
    void close() override;
    void update() override;

    virtual void hideCursor() override;
    void swapBuffers() override;

    int getWidth() const override { return width; }
    int getHeight() const override { return height; }
    std::string getName() const override { return name; }

private:
    void setupCallBacks(std::shared_ptr<EventManager>& eventManager);
    void setupKeyboardCallBacks(std::shared_ptr<EventManager>& eventManager);
    void setupMouseCallBacks(std::shared_ptr<EventManager>& eventManager);
    void setupWindowCallBacks(std::shared_ptr<EventManager>& eventManager);

private:
    GLFWwindow* windowHandle;

    int width, height;
    const std::string name;

    std::unique_ptr<GLFWRenderingContext> renderingContext;
};