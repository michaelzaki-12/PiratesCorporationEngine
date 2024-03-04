//
// Created by pirates on 02/02/24.
//

#include "PiratesImgui.h"

void PiratesImgui::Imgui_init(GLFWwindow* window) {
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // IF using Docking Branch


    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
    ImGui_ImplOpenGL3_Init();

}

void PiratesImgui::UpdateImgui() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

}

void PiratesImgui::ImGui_Init_Viewport(OpenGLFrameBuffer frameBuffer) {
    ImGuiWindowClass window_class;
    window_class.DockNodeFlagsOverrideSet = ImGuiDockNodeFlags_NoTabBar;
    ImGui::SetNextWindowClass(&window_class);
    ImGui::Begin("ViewPort");
    //ImVec2 PanelSize = ImGui::GetContentRegionAvail();
    float window_width = ImGui::GetContentRegionAvail().x;
    float window_height = ImGui::GetContentRegionAvail().y;
    frameBuffer.Scale(window_width, window_height);
    glViewport(0, 0, window_width, window_height);

    //ImVec2 pos = ImGui::GetCursorScreenPos();
    ImGui::Image((void*)(uint64_t)frameBuffer.TEXID, ImVec2{window_width, window_height}, ImVec2{0, 1}, ImVec2{1, 0});
    ImGui::End();

}

void PiratesImgui::ImGui_Delete() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

}
