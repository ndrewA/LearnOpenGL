#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <iostream>
#include <string>
#include <fstream>
#include <iterator>

static std::string getShaderString(const std::string path)
{
    std::fstream file(path);
    if (!file.is_open())
    {
        std::cout << "cannot open file\n";
        return "";
    }
    std::string shaderString(std::istreambuf_iterator<char>{file}, {});
    return shaderString;
}

static unsigned int makeShader(const std::string shaderPath, const unsigned int shaderType)
{
    unsigned int shader = glCreateShader(shaderType);

    std::string shaderString = getShaderString(shaderPath);
    char* shaderSource = new char[shaderString.length() + 1];
    strcpy(shaderSource, shaderString.c_str());
    glShaderSource(shader, 1, &shaderSource, nullptr);
    glCompileShader(shader);

    int succes;
    const unsigned int infoLogLength = 512;
    char infoLog[infoLogLength];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &succes);

    if (!succes) {
        glGetShaderInfoLog(shader, infoLogLength, nullptr, infoLog);
        std::cout << (shaderType == GL_VERTEX_SHADER ? "vertex" : "fragment") 
                  << " shader compilation failed: " << infoLog << '\n';
        __debugbreak();
    }
    return shader;
}

static unsigned int makeProgram(const std::string vertexPath, const std::string fragmentPath)
{
    unsigned int vertexShader = makeShader("src/Shaders/shader.vert", GL_VERTEX_SHADER);
    unsigned int fragmentShader = makeShader("src/Shaders/shader.frag", GL_FRAGMENT_SHADER);
    unsigned int shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    int succes;
    const unsigned int infoLogLength = 512;
    char infoLog[infoLogLength];

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &succes);
    if (!succes) {
        glGetProgramInfoLog(shaderProgram, infoLogLength, nullptr, infoLog);
        std::cout << "program failed: " << infoLog << '\n';
        __debugbreak();
    }

    return shaderProgram;
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

    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;

    float vertices[] = {
        0.5f,  0.5f, 0.0f,  // top right
        0.5f, -0.5f, 0.0f,  // bottom right
       -0.5f, -0.5f, 0.0f,  // bottom left
       -0.5f,  0.5f, 0.0f   // top left 
    };

    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };

    unsigned int vertexArray;
    glGenVertexArrays(1, &vertexArray);
    glBindVertexArray(vertexArray);

    unsigned int vertexBuffer;
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    unsigned int elementBuffer;
    glGenBuffers(1, &elementBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    unsigned int shaderProgram = makeProgram("src/Shaders/shader.vert", "src/Shaders/shader.frag");

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClearColor(0.2f, 0.3f, 0.6f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);
        glBindVertexArray(vertexArray);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}