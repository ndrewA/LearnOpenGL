#pragma once

#include <filesystem>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Platform/OpenGL/OpenGLprogram.h"
#include "Camera.h"
#include "Model.h"
#include "ECS/ECSManager.h"
#include "Inputs/InputManager.h"

#include "Application.h"

#include "ECS/ARchetypeIdentifier.h"

const unsigned int SCR_WIDTH = 1920;
const unsigned int SCR_HEIGHT = 1080;

Camera camera({ 0.0f, 0.0f, 3.0f });

float deltaTime = 0.0f;
float lastFrame = 0.0f;

bool keyIsPressed(int key)
{
    return glfwGetKey(glfwGetCurrentContext(), key) == GLFW_PRESS;
}

void processInput(const int key)
{
    char directionMask = 0x0;
    switch (key) {
        case GLFW_KEY_W:
            directionMask |= direction::front; 
            break;
        case GLFW_KEY_S: 
            directionMask |= direction::back; 
            break; 
        case GLFW_KEY_A: 
            directionMask |= direction::left; 
            break; 
        case GLFW_KEY_D: 
            directionMask |= direction::right; 
            break; 
        case GLFW_KEY_SPACE: 
            directionMask |= direction::up; 
            break; 
        case GLFW_KEY_LEFT_SHIFT: 
            directionMask |= direction::down; 
            break; 
    }
    camera.processKeyboard(directionMask);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void mouse_callback(double xPos, double yPos)
{
    static float lastX = 0.0f;
    static float lastY = 0.0f;

    static bool isFirstMovememnt = true;
    if (isFirstMovememnt) {
        lastX = (float)xPos;
        lastY = (float)yPos;
        isFirstMovememnt = false;
    }

    float xOffset = (float)xPos - lastX;
    float yOffset = (float)yPos - lastY;

    lastX = (float)xPos;
    lastY = (float)yPos;

    camera.processMouseMovement(xOffset, yOffset);
}

void scroll_callback(double xOffset, double yOffset)
{
    camera.processMouseScroll((float)yOffset);
}

class TestComponent
{

};

class c1 {};
class c2 {};
class c3 {};
class c4 {};

void TestFunc(Entity e, c1& c)
{

}

class TestSystem : public System
{
public:
    virtual void onAdded() override { };
    virtual void update(const float deltaTime, SystemContext& context) override
    {
        context.updateEntitiesWithComponents<TestComponent, c1>(
            [this](Entity entity, TestComponent& component, c1& c)
            {
                std::cout << "IN UPDATE FUNCTION: " << entity.index << '\n';
            });
    };
    virtual void onRemoved() override {};
};

class TestSystem1 : public System
{
public:
    virtual void onAdded() override { };
    virtual void update(const float deltaTime, SystemContext& context) override
    {
        context.updateEntitiesWithComponents<c1>(
            [this](Entity entity, c1& c)
            {
                std::cout << "IN UPDATE FUNCTION 1: " << entity.index << '\n';
            });
    };
    virtual void onRemoved() override {};
};

int main()
{
    std::cout << identifier<c1, c2, c3, c4>() << '\n';
    std::cout << identifier<c1, c3, c2, c4>() << '\n';
    std::cout << identifier<c4, c3, c2, c1>() << '\n';
    std::cout << identifier<c2, c1, c3>() << '\n';
    std::cout << identifier<c4, c3, c1>() << '\n';
    std::cout << identifier<c3        >() << '\n';
    std::cout << identifier<c3, c2, c1>() << '\n';

    return 0;
    Application app;
    app.run();
    app.stop();
    return 0;
    bool shouldClose = false;

    EventManager eventManager;

    GLFWWindow window(SCR_WIDTH, SCR_HEIGHT, "test", eventManager);
   
    auto t1 = eventManager.registerListenerFor<WindowResizeEvent>([](const WindowResizeEvent& event) {
        //std::cout << "WindowResizeEvent!\n";
        glViewport(0, 0, event.getWidth(), event.getHeight());
        return false;
    });

    auto t2 = eventManager.registerListenerFor<MouseMoveEvent>([](const MouseMoveEvent& event) {
        //std::cout << "MouseMoveEvent!\n";
        mouse_callback(event.getMouseX(), event.getMouseY());
        return false;
    });

    auto t3 = eventManager.registerListenerFor<MouseScrollEvent>([](const MouseScrollEvent& event) {
        //std::cout << "MouseScrollEvent!\n";
        scroll_callback(event.getMouseX(), event.getMouseY());
        return false;
    });

    auto t4 = eventManager.registerListenerFor<WindowCloseEvent>([&shouldClose](const WindowCloseEvent& event) {
        //std::cout << "WindowCloseEvent!\n";
        shouldClose = true;
        return false;
    });

    auto t5 = eventManager.registerListenerFor<KeyboardPressEvent>([](const KeyboardPressEvent& event) {
        //std::cout << "KeyboardPressEvent!\n";
        processInput(event.getKeyCode());
        return false;
        });

    auto t6 = eventManager.registerListenerFor<CharPressEvent>([](const CharPressEvent& event) {
        //std::cout << (char)event.getCodePoint();
        //processInput(event.getKeyCode());
        return false;
    });
    
    InputManager inputManager(eventManager);

    window.hideCursor();
    //std::cout << "here\n";
    //return 0;
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_STENCIL_TEST);
    // glDepthFunc(GL_ALWAYS);
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    std::string shaderVertexPath = std::filesystem::absolute("../LearnOpengl/src/Platform/OpenGL/Shaders/shader.vert").string();
    std::string shaderFragmentPath = std::filesystem::absolute("../LearnOpengl/src/Platform/OpenGL/Shaders/shader.frag").string();
    auto ourProgram = std::make_shared<OpenGLProgram>(shaderVertexPath, shaderFragmentPath);

    std::string modelPath = std::filesystem::absolute("../LearnOpengl/res/backpack/backpack.obj").generic_string();
    Model ourModel(modelPath);

    size_t frames = 0;
    Timer t;
    while (!shouldClose)
    {
        glStencilMask(0x00);
        if (t.getDeltaTime() >= 1.0f) {
            std::cout << "fps: " << static_cast<float>(frames) / t.getDeltaTime() << '\n';
            t.mark();
            frames = 0;
        }
        frames++;

        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        
        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        ourProgram->bind();

        glm::mat4 projection = glm::perspective(camera.getFOV(), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.getViewMatrix();
        ourProgram->setUniform("projection", projection);
        ourProgram->setUniform("view", view);

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); 
        ourProgram->setUniform("model", model);
        ourModel.draw(ourProgram);

        eventManager.publishEvents();
        window.update();
    }

    return 0;
}
