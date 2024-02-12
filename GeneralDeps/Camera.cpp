//
// Created by pirates on 01/02/24.
//
#include "Camera.h"

Camera::Camera(int width, int height, glm::vec3 position) {
    Camera::width = width;
    Camera::height = height;
    Camera::Position = position;
}

void Camera::Matrix(float Fovdeg, float nearplane, float farplane, Shader &shader, const char *uniform) {

    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 Projection = glm::mat4(1.0f);

    view = glm::lookAt(Position, Position + Orientation, UP);
    Projection = glm::perspective(glm::radians(Fovdeg),(float)(width / height), nearplane, farplane);
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(Projection * view));
}

void Camera::Inputs(GLFWwindow *window) {

    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
        Position += speed * Orientation;
    }
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
        Position -= speed * Orientation;
    }
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
        Position += speed * -glm::normalize(glm::cross(Orientation, UP));
    }
    if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS){
        Position += speed * -UP;
    }
    if(glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS){
        Position += speed * UP;
    }
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
        Position += speed * glm::normalize(glm::cross(Orientation, UP));
    }
    if(glfwGetKey(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS){
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

        if(firstClick){
            glfwSetCursorPos(window, (width / 2), (height / 2));
            firstClick = false;

        }
        double mouseX, mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);
        float rotX = sensitivity * (float)(mouseY - (height / 2)) / height;
        float rotY = sensitivity * (float)(mouseX - (height / 2)) / height;

        // Calculates upcoming vertical change in the Orientation
        glm::vec3 newOrientation = glm::rotate(Orientation, glm::radians(-rotX), glm::normalize(glm::cross(Orientation, UP)));

        // Decides whether or not the next vertical Orientation is legal or not
        if (!((glm::angle(newOrientation, UP) <= glm::radians(5.0f) or(glm::angle(newOrientation, -UP) <= glm::radians(5.0f)))))
        {
            Orientation = newOrientation;
        }

        // Rotates the Orientation left and right
        Orientation = glm::rotate(Orientation, glm::radians(-rotY), UP);

        // Sets mouse cursor to the middle of the screen so that it doesn't end up roaming around
        glfwSetCursorPos(window, (width / 2), (height / 2));
        ImGui::SetCursorPos(ImVec2{(float)(width / 2), (float)(height / 2)});


    }else if(glfwGetKey(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE){
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        firstClick = true;

    }

}

void Camera::UpdateCamera(int width, int height, glm::vec3 position) {
    Camera::width = width;
    Camera::height = height;
    Camera::Position = position;
}
