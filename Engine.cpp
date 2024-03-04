//
// Created by pirates on 27/09/23.
//
#include "Engine.h"

float width, height;

int main() {

    //initialize glfw
    glfwInit();
    GLFWmonitor *monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode *mode = glfwGetVideoMode(monitor);
    glfwWindowHint(GLFW_RED_BITS, mode->redBits);
    glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
    glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
    glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
    width = mode->width;
    height = mode->height;

    double time = glfwGetTime();

// Vertices coordinates
    GLfloat Vertices[] =
            { //     COORDINATES     /        COLORS          /    TexCoord   /        NORMALS       //
                    -1.0f, 0.0f,  1.0f,		0.0f, 0.0f, 0.0f,		0.0f, 0.0f,		0.0f, 1.0f, 0.0f,
                    -1.0f, 0.0f, -1.0f,		0.0f, 0.0f, 0.0f,		0.0f, 1.0f,		0.0f, 1.0f, 0.0f,
                    1.0f, 0.0f, -1.0f,		0.0f, 0.0f, 0.0f,		1.0f, 1.0f,		0.0f, 1.0f, 0.0f,
                    1.0f, 0.0f,  1.0f,		0.0f, 0.0f, 0.0f,		1.0f, 0.0f,		0.0f, 1.0f, 0.0f
            };

// Indices for vertices order
    GLuint IndexBuffer[] =
            {
                    0, 1, 2,
                    0, 2, 3
            };

    GLfloat lightVertices[] =
            { //     COORDINATES     //
                    -0.1f, -0.1f, 0.1f,
                    -0.1f, -0.1f, -0.1f,
                    0.1f, -0.1f, -0.1f,
                    0.1f, -0.1f, 0.1f,
                    -0.1f, 0.1f, 0.1f,
                    -0.1f, 0.1f, -0.1f,
                    0.1f, 0.1f, -0.1f,
                    0.1f, 0.1f, 0.1f
            };

    GLuint lightIndices[] =
            {
                    0, 1, 2,
                    0, 2, 3,
                    0, 4, 7,
                    0, 7, 3,
                    3, 7, 6,
                    3, 6, 2,
                    2, 6, 5,
                    2, 5, 1,
                    1, 5, 4,
                    1, 4, 0,
                    4, 5, 6,
                    4, 6, 7
            };

    // giving glfw information about our opengl version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

    //initializing glfw window
    GLFWwindow *window = glfwCreateWindow(width, height, "PiratesEngine", NULL, NULL);
    if (window == NULL) {
        std::cout << "failed to Create glfw Window" << std::endl;
        glfwTerminate();
        return -1;
    }
    // making our current window the window we just created
    glfwMakeContextCurrent(window);
    std::shared_ptr<PiratesImgui> Gui;
    Gui->Imgui_init(window);
    //loading opengl using glad
    gladLoadGL();

    //setting our viewport to be our glfw window
    glViewport(0, 0, width, height);
    GLFWimage images[1];
    images[0].pixels = stbi_load("Textures/Pirates.png", &images[0].width, &images[0].height, 0, 4); //rgba channels
    glfwSetWindowIcon(window, 1, images);
    stbi_image_free(images[0].pixels);
    Shader shader("inc/default.vert", "inc/default.frag");

    VertexArrayObject VAO;
    VAO.Bind();

    VertexBufferObject VBO(Vertices, sizeof(Vertices));
    IndexBufferObject IBO(IndexBuffer, sizeof(IndexBuffer));

    VAO.LinkVBO(VBO, 0, 4, GL_FLOAT, 11 * sizeof(GL_FLOAT), nullptr);
    VAO.LinkVBO(VBO, 1, 4, GL_FLOAT, 11 * sizeof(GL_FLOAT), (void *) (3 * sizeof(GL_FLOAT)));
    VAO.LinkVBO(VBO, 2, 4, GL_FLOAT, 11 * sizeof(GL_FLOAT), (void *) (6 * sizeof(GL_FLOAT)));
    VAO.LinkVBO(VBO, 3, 4, GL_FLOAT, 11 * sizeof(GL_FLOAT), (void *) (8 * sizeof(GL_FLOAT)));

    VAO.UnBind();
    VBO.UnBind();
    IBO.UnBind();

    // Shader for light cube
    Shader lightShader("inc/light.vert", "inc/light.frag");
    // Generates Vertex Array Object and binds it
    VertexArrayObject lightVAO;
    lightVAO.Bind();
    // Generates Vertex Buffer Object and links it to vertices
    VertexBufferObject lightVBO(lightVertices, sizeof(lightVertices));
    // Generates Element Buffer Object and links it to indices
    IndexBufferObject lightIBO(lightIndices, sizeof(lightIndices));
    // Links VBO attributes such as coordinates and colors to VAO
    lightVAO.LinkVBO(lightVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void *) 0);
    // Unbind all to prevent accidentally modifying them
    lightVAO.UnBind();
    lightVBO.UnBind();
    lightIBO.UnBind();


    glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
    glm::mat4 lightModel = glm::mat4(1.0f);
    lightModel = glm::translate(lightModel, lightPos);

    glm::vec3 pyramidPos = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::mat4 pyramidModel = glm::mat4(1.0f);
    pyramidModel = glm::translate(pyramidModel, pyramidPos);


    lightShader.Activate();
    glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
    glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z,
                lightColor.w);
    shader.Activate();
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(pyramidModel));
    glUniform4f(glGetUniformLocation(shader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
    glUniform3f(glGetUniformLocation(shader.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

    const char *PiratesTexture = "Textures/Pirates.png";
    Texture Texture(PiratesTexture);
    OpenGLFrameBuffer FrameBuffer;
    FrameBuffer.GenerateFrameBuffer(width, height);

    GLuint tex0Uni = glGetUniformLocation(shader.ID, "tex0");
    shader.Activate();
    glUniform1i(tex0Uni, 0);
    GLfloat NumOfVert = sizeof(Vertices) / sizeof(GLfloat);

    GLuint uniID = glGetUniformLocation(shader.ID, "scale");

    //executing the color of the window
    glClear(GL_COLOR_BUFFER_BIT);
    Camera camera(width, height, glm::vec3(0.0f, 0.0f, 3.0f));

    //swapping the buffers to our glfw window
    glEnable(GL_DEPTH_TEST);
    //WindowEvents* PiratesWindowEvents = new WindowEvents;
    //WindowEvents* PiratesWindowEvents = new WindowEvents;
    std::shared_ptr<WindowEvents> PiratesWindowEvents = std::make_shared<WindowEvents>();
    int Width = 0, Height = 0;
    PiratesWindowEvents->width = Width;
    PiratesWindowEvents->height = Height;
    GLuint IMTex = Texture::LoadTexture("Textures/Pirates.png");

    //checking that glfw window not closing directly
    while (!glfwWindowShouldClose(window)) {
        int WInPixel = 0, HInPixel = 0;
        //glfwGetWindowSize(window, &Width, &Height);
        PiratesWindowEvents->OnUpdate(window);
        if (Width != width || Height != height) {
            PiratesWindowEvents->UpdateFrameBuffer(window, WInPixel, HInPixel);
        }
        Gui->UpdateImgui();
        ImGui::DockSpaceOverViewport();


        ImGui::BeginMainMenuBar();
        ImGui::Button("Settings");

        ImGui::EndMainMenuBar();

        ImGui::StyleColorsLight();
        Gui->ImGui_Init_Viewport(FrameBuffer);
        // giving the color of window
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        double crnttime = glfwGetTime();
        if (crnttime - time >= (1 / 60)) {
            crnttime = time;
        }
        camera.Inputs(window);
        camera.UpdateMatrix(45.0f, 1.0f, 100.0f);


        //executing the color of the window
        FrameBuffer.Bind();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.Activate();
        glUniform3f(glGetUniformLocation(shader.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
        camera.Matrix(shader, "camMatrix");

        glUniform1f(uniID, 0.5f);
        Texture.Bind();

        VAO.Bind();
        glDrawElements(GL_TRIANGLES, sizeof(IndexBuffer) / sizeof(int), GL_UNSIGNED_INT, nullptr);

        lightShader.Activate();
        camera.Matrix(lightShader, "camMatrix");
        lightVAO.Bind();
        glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(int), GL_UNSIGNED_INT, nullptr);

        FrameBuffer.UNBind();


        ImGui::Begin("Properties");
        ImGui::Text("Vertices");
        ImGui::Text("%f", NumOfVert * ((float) 3 / 8));
        ImGui::Text("Texture: ");
        ImGui::Image((void *) (uint64_t) IMTex, ImVec2{64, 64}, ImVec2{0, 1}, ImVec2{1, 0});

        ImGui::End();


        // Rendering
        // (Your code clears your framebuffer, renders your other stuff etc.)
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        // (Your code calls glfwSwapBuffers() etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();

    }
//    delete PiratesWindowEvents;
    VAO.Delete();
    VBO.Delete();
    IBO.Delete();
    lightVAO.Delete();
    lightShader.Delete();
    shader.Delete();
    Texture.Delete();
    Texture.DeleteLoadTexture(IMTex);
    Gui->ImGui_Delete();
    //delete PiratesWindowEvents;
    //destroying opengl window and termination of glfw
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}