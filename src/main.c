#include <stdlib.h>
#include <stdio.h>
#include <glad/gl.h>
#include <GLFW/glfw3.h>

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, 1);
}

int main()
{
    int height = 800; int width = 600;
    float r = 0;float g = 1;float b = 0.5; float rc = 0.01;float gc = -0.01;float bc = 0.01;
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "GL_Engine", NULL, NULL);

    glfwMakeContextCurrent(window);
    gladLoaderLoadGL();
    glViewport(0, 0, 800, 600);

    while(!glfwWindowShouldClose(window))
    {
        if (r >= 1){r=-0.01;}
        else if(r<=0){rc=0.01;}
        r=r+rc;

        if (g >= 1){g=-0.01;}
        else if(g<=0){gc=0.01;}
        g=g+gc;

        if (b >= 1){b=-0.01;}
        else if(b<=0){bc=0.01;}
        b=b+bc;

        processInput(window);
        glClearColor(r, g, b, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);



        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    return 0;
}
