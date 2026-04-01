#include <stdlib.h> 
#include <stdio.h> 
#include <glad/gl.h> 
#include <GLFW/glfw3.h> 
#include <math.h> 
#include <shader.h>
#include <camera.h>  
#include <iostream> 
#include <stb_image.h> 
#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtc/type_ptr.hpp> 
#include <imgui.h> 
#include <imgui/backends/imgui_impl_glfw.h> 
#include <imgui/backends/imgui_impl_opengl3.h>

bool firstMouse = true;
float lastX =  400.0f;
float lastY =  300.0f;
int scr_Width = 800, scr_Height = 600;
float deltaTime = 0.0f; // Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame
glm::mat4 view = glm::mat4(1.0f);
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

void processInput(GLFWwindow *window)
    {    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){glfwSetWindowShouldClose(window, 1);}

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){camera.ProcessKeyboard(FORWARD, deltaTime);}
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){camera.ProcessKeyboard(BACKWARD, deltaTime);}
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){camera.ProcessKeyboard(LEFT, deltaTime);}
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){camera.ProcessKeyboard(RIGHT, deltaTime);}

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS){camera.ProcessKeyboard(UP, deltaTime);}
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS){camera.ProcessKeyboard(DOWN, deltaTime);}

    if (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS){glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);}
};

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

int main()
{
    printf("Screen Width: ");
    scanf("%d", &scr_Width);
    printf("Screen Height: ");
    scanf("%d", &scr_Height);
    lastX =  scr_Width  / 2.0;
    lastY =  scr_Height / 2.0;
    glm::vec4 color =glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

    float vertices[] = {// Cord, color, text
         0.5f, -0.288f, 0.5f, 	1.0f, 0.0f, 0.0f,	5.0f,0.0f, 
        -0.5f, -0.288f, 0.5f, 	0.0f, 1.0f, 0.0f,	0.0f,0.0f,  //front triangle
         0.0f,  0.577f, 0.5f,   0.0f, 0.0f, 1.0f,   2.5f,5.0f,


         0.0f,  0.577f, 0.5f,   1.0f, 0.0f, 0.0f,   0.0f,5.0f, 
         0.5f, -0.288f, 0.5f,   0.0f, 1.0f, 0.0f,   0.0f,0.0f,  
         0.5f, -0.288f,-0.5f,   0.0f, 0.0f, 1.0f,   5.0f,0.0f,
                                                                //right wall
         0.0f,  0.577f, 0.5f,   1.0f, 0.0f, 0.0f,   0.0f,5.0f, 
         0.5f, -0.288f,-0.5f,   0.0f, 0.0f, 1.0f,   5.0f,0.0f,  
         0.0f,  0.577f,-0.5f,   0.0f, 1.0f, 0.0f,   5.0f,5.0f, 


         0.5f, -0.288f, 0.5f,   0.0f, 0.0f, 1.0f,   5.0f,5.0f, 
        -0.5f, -0.288f, 0.5f,   0.0f, 1.0f, 0.0f,   0.0f,5.0f,  
         0.5f, -0.288f,-0.5f,   1.0f, 0.0f, 0.0f,   5.0f,0.0f,
                                                                //Bottom wall
         0.5f, -0.288f,-0.5f,   1.0f, 0.0f, 0.0f,   5.0f,0.0f, 
        -0.5f, -0.288f, 0.5f,   0.0f, 1.0f, 0.0f,   0.0f,5.0f,  
        -0.5f, -0.288f,-0.5f,   0.0f, 0.0f, 1.0f,   0.0f,0.0f, 


        -0.5f, -0.288f,-0.5f,   1.0f, 0.0f, 0.0f,   0.0f,0.0f, 
        -0.5f, -0.288f, 0.5f,   0.0f, 1.0f, 0.0f,   5.0f,0.0f,  
         0.0f,  0.577f, 0.5f,   0.0f, 0.0f, 1.0f,   5.0f,5.0f,
                                                                //Left wall
        -0.5f, -0.288f,-0.5f,   1.0f, 0.0f, 0.0f,   0.0f,0.0f, 
         0.0f,  0.577f,-0.5f,   0.0f, 1.0f, 0.0f,   0.0f,5.0f,  
         0.0f,  0.577f, 0.5f,   0.0f, 0.0f, 1.0f,   5.0f,5.0f, 


         0.5f, -0.288f,-0.5f,   1.0f, 0.0f, 0.0f,   0.0f,0.0f, 
        -0.5f, -0.288f,-0.5f,   0.0f, 1.0f, 0.0f,   5.0f,0.0f,  //Back triangle
         0.0f,  0.577f,-0.5f,   0.0f, 0.0f, 1.0f,   2.5f,5.0f
    };

    glm::vec3 prisimPositions[] = {
    glm::vec3( 0.0f,  0.0f,  0.0f), 
    glm::vec3(-1.5f, -2.2f,  -2.5f),  
    glm::vec3(-3.8f, -2.0f, -12.3f),  
    glm::vec3( 2.4f, -0.4f,  -3.5f),  
    glm::vec3(-1.7f,  3.0f,  -7.5f),  
    glm::vec3( 1.3f, -2.0f,  -2.5f),  
    glm::vec3( 1.5f,  2.0f,  -2.5f), 
    glm::vec3( 1.5f,  0.2f,  -1.5f), 
    glm::vec3(-1.3f,  1.0f,  -1.5f)  
};

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    GLFWwindow* window = glfwCreateWindow(scr_Width, scr_Height, "GL_Engine", NULL, NULL);
    glfwMakeContextCurrent(window);
    gladLoaderLoadGL();

    lastX = scr_Width/2, lastY = scr_Height/2;
    glfwSetCursorPosCallback(window, mouse_callback);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();

    Shader ourShader("shaders/vertex_shader.glsl", "shaders/fragment_shader.glsl");
    glEnable(GL_DEPTH_TEST);  

    glViewport(0, 0, scr_Width, scr_Height);


// note that we're translating the scene in the reverse direction of where we want to move
    glm::mat4 projection = glm::perspective(glm::radians(camera.Fov), (float)scr_Width/scr_Height, 0.1f, 100.0f);
	
	int Texwidth, Texheight, nrChannels;
	unsigned char *data1 = stbi_load("Textures/wall.jpg", &Texwidth, &Texheight, &nrChannels, 0);
    if (!data1){return 0;}
	unsigned int texture1;
	glGenTextures(1, &texture1);
    glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
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

    unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");
    int modelLoc = glGetUniformLocation(ourShader.ID, "model");
    int viewLoc = glGetUniformLocation(ourShader.ID, "view");
    int projLoc = glGetUniformLocation(ourShader.ID, "projection");

    ourShader.use(); // don't forget to activate the shader before setting uniforms!  
    glUniform1i(glGetUniformLocation(ourShader.ID, "texture1"), 0); // set it manually
    ourShader.setInt("texture2", 1);

    while(!glfwWindowShouldClose(window))
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGui::Begin("Controls");

        ImGui::ColorEdit3("Clear Color", (float*)&color);

        ImGui::Text("FPS: %.1f", deltaTime > 0.0f ? 1.0f / deltaTime : 0.0f);

        ImGui::End();

        float timeValue = glfwGetTime();
        deltaTime = timeValue - lastFrame;
        lastFrame = timeValue;  

        processInput(window);
        glClearColor(color.x, color.y, color.z, color.w);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        view = camera.GetViewMatrix();

        // render the triangle
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

        glm::mat4 trans = glm::mat4(1.0f);
        //trans = glm::translate(trans, glm::vec3(go-0.5, ro-0.5, 0.0f));
        //trans = glm::rotate(trans, timeValue, glm::vec3(0.0f, 0.0f, 1.0f));
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);
        glBindVertexArray(VAO[0]);
        for(unsigned int i = 1; i < 11; i++){
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, prisimPositions[i]);
            float angle = 20.0f * i; 
            if(i % 3 == 0){angle*=timeValue;}
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
            glDrawArrays(GL_TRIANGLES, 0, 24);
        }

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}
