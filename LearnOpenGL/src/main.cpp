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

    const int WINDOW_WIDTH = 1920;
    const int WINDOW_HEIGHT = 1080;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "OpenGL", NULL, NULL);
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
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
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

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    unsigned int lightVertexArray;
    glGenVertexArrays(1, &lightVertexArray);
    glBindVertexArray(lightVertexArray);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    Shader cubeShader("src/Shaders/CubeShaders/shader.vert", 
                      "src/Shaders/CubeShaders/shader.frag");
    Shader lighShader("src/Shaders/ShaderForLightSources/shader.vert", 
                      "src/Shaders/ShaderForLightSources/shader.frag");

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    stbi_set_flip_vertically_on_load(true);

    int width, height, channelNumber;
    unsigned char* data = stbi_load("res/container2.png", &width, &height, &channelNumber, 0);

    if (!data) {
        std::cout << "TEXTURE DIDNT LOAD\n";
        __debugbreak();
    }

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);

    cubeShader.use();
    cubeShader.setInt("material.diffuse", 0);

    unsigned int textureOutline;

    data = stbi_load("res/container2_specular.png", &width, &height, &channelNumber, 0);

    if (!data) {
        std::cout << "TEXTURE DIDNT LOAD\n";
        __debugbreak();
    }

    glGenTextures(1, &textureOutline);
    glBindTexture(GL_TEXTURE_2D, textureOutline);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);

    cubeShader.use();
    cubeShader.setInt("material.specular", 1);

    glEnable(GL_DEPTH_TEST);

    glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

    glm::vec3 cubePositions[] = {
    glm::vec3(0.0f,  0.0f,  0.0f),
    glm::vec3(2.0f,  5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3(2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f,  3.0f, -7.5f),
    glm::vec3(1.3f, -2.0f, -2.5f),
    glm::vec3(1.5f,  2.0f, -2.5f),
    glm::vec3(1.5f,  0.2f, -1.5f),
    glm::vec3(-1.3f,  1.0f, -1.5f)
    };


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        //glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);

        checkKeyboard(window);
        glm::mat4 view = camera.getViewMatrix();
    
        glm::mat4 projection;
        projection = glm::perspective(camera.getFOV(), (float)WINDOW_WIDTH/WINDOW_HEIGHT, 0.1f, 100.0f);

        cubeShader.use();

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, textureOutline);

        cubeShader.setInt("material.specular", 1);
        cubeShader.setFloat("material.shininess", 128.0f);

        cubeShader.setVec3("light.ambient", { 0.4f, 0.4f, 0.4f });
        cubeShader.setVec3("light.diffuse", { 0.9f, 0.9f, 0.9f });
        cubeShader.setVec3("light.specular", { 1.0f, 1.0f, 1.0f });
        
        cubeShader.setVec3("light.position", camera.getPosition());
        cubeShader.setVec3("light.direction", camera.getFront());
        cubeShader.setFloat("light.innerCutOff", glm::cos(glm::radians(12.5f)));
        cubeShader.setFloat("light.outerCutOff", glm::cos(glm::radians(17.5f)));

        cubeShader.setFloat("light.constant", 1.0f);
        cubeShader.setFloat("light.linear", 0.09f);
        cubeShader.setFloat("light.quadratic", 0.032f);

        cubeShader.setVec3("viewPos", camera.getPosition());

        cubeShader.setMat4("view", view);

        cubeShader.setMat4("projection", projection);

        //glm::mat4 model = glm::mat4(1.0f);

        //cubeShader.setMat4("model", model);

        //glBindVertexArray(cubeVertexArray);
        //glDrawArrays(GL_TRIANGLES, 0, 36);

        for (unsigned int i = 0; i < 10; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            cubeShader.setMat4("model", model);

            glBindVertexArray(cubeVertexArray);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        lighShader.use();

        lighShader.setMat4("view", view);

        lighShader.setMat4("projection", projection);

        glm::mat4 lightModel = glm::mat4(1.0f);
        lightModel = glm::translate(lightModel, lightPos);
        lightModel = glm::scale(lightModel, glm::vec3(0.2f));
        lighShader.setMat4("model", lightModel);

        glBindVertexArray(lightVertexArray);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &cubeVertexArray);
    glDeleteVertexArrays(1, &lightVertexArray);

    glfwTerminate();
    return 0;
}