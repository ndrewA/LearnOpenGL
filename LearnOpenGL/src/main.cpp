#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stb_image/stb_image.h>

#include <iostream>

#include "Shader.h"
#include "Camera.h"

Camera camera;

static void mouseMoveCallBack(GLFWwindow* window, double xPos, double yPos)
{
    static float lastX = 0.0f;
    static float lastY = 0.0f;

    float xOffset = (float)xPos - lastX;
    float yOffset = (float)yPos - lastY;

    lastX = (float)xPos;
    lastY = (float)yPos;

    camera.processMouseMovement(xOffset, yOffset);
}

static void scrollCallBack(GLFWwindow* window, double xOffset, double yOffset)
{
    camera.processMouseScroll((float)yOffset);
}

bool keyIsPressed(GLFWwindow* window, int key)
{
    return glfwGetKey(window, key) == GLFW_PRESS;
}

static void checkKeyboard(GLFWwindow* window)
{
    char directionMask = 0x0;
    if (keyIsPressed(window, GLFW_KEY_W))
        directionMask |= Camera::direction::front;
    if (keyIsPressed(window, GLFW_KEY_S))
        directionMask |= Camera::direction::back;
    if (keyIsPressed(window, GLFW_KEY_A))
        directionMask |= Camera::direction::left;
    if (keyIsPressed(window, GLFW_KEY_D))
        directionMask |= Camera::direction::right;
    camera.processKeyboard(directionMask);
}

int main()
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "failed to initialize GLAD" << std::endl;
        return -1;
    }

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwSetCursorPosCallback(window, mouseMoveCallBack);
    glfwSetScrollCallback(window, scrollCallBack);

    float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };

    unsigned int indices[] = {
        0, 1, 2,
        0, 2, 3
    };

    unsigned int vertexBuffer;
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    unsigned int elementBuffer;
    glGenBuffers(1, &elementBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    unsigned int cubeVertexArray;
    glGenVertexArrays(1, &cubeVertexArray);
    glBindVertexArray(cubeVertexArray);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    unsigned int lightVertexArray;
    glGenVertexArrays(1, &lightVertexArray);
    glBindVertexArray(lightVertexArray);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    Shader cubeShader("src/Shaders/CubeShaders/shader.vert", 
                      "src/Shaders/CubeShaders/shader.frag");
    Shader lighShader("src/Shaders/ShaderForLightSources/shader.vert", 
                      "src/Shaders/ShaderForLightSources/shader.frag");

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glEnable(GL_DEPTH_TEST);

    glm::vec3 lightPos{ 1.2f, 1.0f, 2.0f };

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */

        //glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);

        checkKeyboard(window);
        glm::mat4 view = camera.getViewMatrix();
    
        glm::mat4 projection;
        projection = glm::perspective(camera.getFOV(), 800.0f / 600.0f, 0.1f, 100.0f);

        cubeShader.use();

        cubeShader.setVec3("objectColor", { 1.0f, 0.5f, 0.31f });
        cubeShader.setVec3("lightColor", { 1.0f, 1.0f, 1.0f });
        
        cubeShader.setVec3("lightPos", lightPos);

        cubeShader.setMat4("view", view);

        cubeShader.setMat4("projection", projection);

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, { 1.0f, 0.3f, 0.5f });
        model = glm::rotate(model, glm::radians(20.0f), glm::vec3(1.0f, 0.3f, 0.5f));

        cubeShader.setMat4("model", model);

        glBindVertexArray(cubeVertexArray);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        lighShader.use();

        lighShader.setMat4("view", view);

        lighShader.setMat4("projection", projection);

        model = glm::mat4(1.0f);
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.2f));
        lighShader.setMat4("model", model);

        glBindVertexArray(lightVertexArray);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &cubeVertexArray);
    glDeleteVertexArrays(1, &lightVertexArray);

    glfwTerminate();
    return 0;
}