#include <stdlib.h>
#include <stdio.h>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <shader.h>
#include <iostream>
#include <stb_image.h>

void processInput(GLFWwindow *window,float &mix)
{    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){glfwSetWindowShouldClose(window, 1);}
    if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS){mix+=0.001f;}
    if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS){mix-=0.001f;}
}

int main()
{
    int height = 600; int width = 600;
    float mix=0.0f;

    float vertices[] = {// Cord, color, text
        0.0f,      0.3f, 0.0f, 	1.0f, 0.0f, 0.0f,	5.0f,0.0f,    // bottom-right
        0.2598f, -0.15f, 0.0f, 	0.0f, 1.0f, 0.0f,	0.0f,0.0f,   // bottom-left
        -0.2598f,-0.15f, 0.0f, 	0.0f, 0.0f, 1.0f,  	2.5f,5.0f   // top
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

    glViewport(0, 0, width, height);
	
	int Texwidth, Texheight, nrChannels;
	unsigned char *data1 = stbi_load("Textures/wall.jpg", &Texwidth, &Texheight, &nrChannels, 0);
    if (!data1){return 0;}
	unsigned int texture1;
	glGenTextures(1, &texture1);
    glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Texwidth, Texheight, 0, GL_RGB, GL_UNSIGNED_BYTE, data1);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data1);


    stbi_set_flip_vertically_on_load(true);  
    unsigned char *data2 = stbi_load("Textures/awesomeface.png", &Texwidth, &Texheight, &nrChannels, 0);
    if (!data2){return 0;}
    unsigned int texture2;
    glGenTextures(1, &texture2);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Texwidth, Texheight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data2);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data2);

    GLuint VBO[2], VAO[2];
    glGenVertexArrays(2, VAO);
    glGenBuffers(2, VBO);
	
	//Triangle
    glBindVertexArray(VAO[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    ourShader.use(); // don't forget to activate the shader before setting uniforms!  
    glUniform1i(glGetUniformLocation(ourShader.ID, "texture1"), 0); // set it manually
    ourShader.setInt("texture2", 1);

    while(!glfwWindowShouldClose(window))
    {
        float timeValue = glfwGetTime();
        float ro = (sin(timeValue) / 2.0f)+0.5f;
        float go = (cos(timeValue) / 2.0f)+0.5f;
        float bo = (tan(timeValue) / 2.0f)+0.5f;

        processInput(window, mix);
        glClearColor(ro, go, bo, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        int FragMix= glGetUniformLocation(ourShader.ID, "FragMix");
        glUniform1f(FragMix,mix);

        // render the triangle
        int vertexOffset= glGetUniformLocation(ourShader.ID, "Offset");
        float xoffset = (timeValue);
        glUniform3f(vertexOffset, xoffset,0.0f,0.0f);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);
        glBindVertexArray(VAO[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}