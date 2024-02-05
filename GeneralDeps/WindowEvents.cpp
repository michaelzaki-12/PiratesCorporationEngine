//
// Created by pirates on 02/02/24.
//

#include "WindowEvents.h"

void WindowEvents::OnUpdate(GLFWwindow * window) {
    glfwGetWindowSize(window, &width, &height);
}

void WindowEvents::UpdateFrameBuffer(GLFWwindow *window, int width_in_pixels, int height_in_Pixels) {
    glfwGetFramebufferSize(window, &width_in_pixels, &height_in_Pixels);
    glViewport(0, 0, width_in_pixels, height_in_Pixels);

}


