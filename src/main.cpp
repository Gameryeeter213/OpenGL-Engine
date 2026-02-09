#include <stdlib.h>
#include <stdio.h>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <shader.h>
#include <iostream>

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, 1);
}

int main()
{
    int height = 600; int width = 600;

    float vertices[] = {
        0.0f, 0.3, 0.0f, 1.0f, 0.0f, 0.0f,   // bottom-right
        0.2598f, -0.15f, 0.0f, 0.0f, 1.0f, 0.0f,   // bottom-left
        -0.2598f,  -0.15f, 0.0f, 0.0f, 0.0f, 1.0f    // top
    };

    float verticesLine[] = {
        1.0f, -0.3f, 0.0f, 1.0f, 0.0f, 0.0f,
        -1.0f, -0.3f, 0.0f, 0.0f, 1.0f, 0.0f
    };

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    GLFWwindow* window = glfwCreateWindow(width, height, "GL_Engine", NULL, NULL);
    glfwMakeContextCurrent(window);
    gladLoaderLoadGL();
    Shader ourShader("shaders/vertex_shader.glsl", "shaders/fragment_shader.glsl");
    Shader LineShader("shaders/vertex_shaderLine.glsl", "shaders/fragment_shaderLine.glsl");

    glViewport(0, 0, width, height);


    GLuint VBO[2], VAO[2];
    glGenVertexArrays(2, VAO);
    glGenBuffers(2, VBO);
    glBindVertexArray(VAO[0]);

    glBindVertexArray(VAO[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);	// Vertex attributes stay the same
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // second line setup
    // ---------------------
    glBindVertexArray(VAO[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesLine), verticesLine, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);	// Vertex attributes stay the same
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);



    while(!glfwWindowShouldClose(window))
    {
        float timeValue = glfwGetTime();
        float ro = (sin(timeValue) / 2.0f)+0.5f;
        float go = (cos(timeValue) / 2.0f)+0.5f;
        float bo = (tan(timeValue) / 2.0f)+0.5f;

        processInput(window);
        glClearColor(ro, go, bo, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // render the triangle
        ourShader.use();
        int vertexOffset= glGetUniformLocation(ourShader.ID, "Offset");
        float xoffset = (timeValue);
        glUniform3f(vertexOffset, xoffset,0.0f,0.0f);
        glBindVertexArray(VAO[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        LineShader.use();
        glBindVertexArray(VAO[1]);
        glDrawArrays(GL_LINES, 0, 2);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}
