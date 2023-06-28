#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Platform/OpenGL/OpenGLprogram.h"
#include "Camera.h"
#include "Model.h"

#include "Events/EventManager.h"
#include "Platform/GLFW/GLFWWindow.h"

#include <filesystem>
#include <iostream>
                                                                #include "Inputs/Inputmanager.h"

#include "ECS/EntityManager.h"
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

bool shouldClose = false;

class test12 : public Component
{

};

int main()
{
    EntityManager manager;
    test12 t324;
    manager.createEntity();
    manager.createEntity();
    manager.createEntity();
    manager.createEntity();
    manager.destroyEntity(1);
    //manager.destroyEntity(1);
    manager.addComponent(1, std::make_shared<test12>());
    manager.getEntitiesWithComponents<test12>();

    //return 0;

    EventManager eventManager;

    GLFWWindow window(SCR_WIDTH, SCR_HEIGHT, "test", eventManager);
   
    eventManager.registerListenerFor<WindowResizeEvent>([](const std::shared_ptr<WindowResizeEvent>& event) {
        //std::cout << "WindowResizeEvent!\n";
        glViewport(0, 0, event->getWidth(), event->getHeight());
    });

    eventManager.registerListenerFor<MouseMoveEvent>([](const std::shared_ptr<MouseMoveEvent>& event) {
        //std::cout << "MouseMoveEvent!\n";
        mouse_callback(event->getMouseX(), event->getMouseY());
    });

    eventManager.registerListenerFor<MouseScrollEvent>([](const std::shared_ptr<MouseScrollEvent>& event) {
        //std::cout << "MouseScrollEvent!\n";
        scroll_callback(event->getMouseX(), event->getMouseY());
    });

    eventManager.registerListenerFor<WindowCloseEvent>([](const std::shared_ptr<WindowCloseEvent>& event) {
        //std::cout << "WindowCloseEvent!\n";
        shouldClose = true;
    });

    eventManager.registerListenerFor<KeyboardPressEvent>([](const std::shared_ptr<KeyboardPressEvent>& event) {
        //std::cout << "KeyboardPressEvent!\n";
        processInput(event->getKeyCode());
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
    utilities::Timer t;
    while (!shouldClose)
    {
        glStencilMask(0x00);
        if (t.getDeltaTime() >= 1.0f) {
            std::cout << "fps: " << static_cast<float>(frames) / t.getDeltaTime() << '\n';
            t.resetTimer();
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
