//
// Created by pirates on 02/02/24.
//

#ifndef PIRATESENGINE_PIRATESIMGUI_H
#define PIRATESENGINE_PIRATESIMGUI_H

#include "../imgui-docking/imgui.h"
#include "../imgui-docking/backends/imgui_impl_glfw.h"
#include "../imgui-docking/backends/imgui_impl_opengl3.h"
#include "../OpenGLFrameBuffer.h"
#include <iostream>

class PiratesImgui {
public:
    void Imgui_init(GLFWwindow *window);
    static void ImGui_Delete();

    void UpdateImgui();
    static void ImGui_Init_Viewport(OpenGLFrameBuffer frameBuffer);
};


#endif //PIRATESENGINE_PIRATESIMGUI_H
