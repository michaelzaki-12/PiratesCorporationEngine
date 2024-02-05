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

}

void Camera::UpdateCamera(int width, int height, glm::vec3 position) {
    Camera::width = width;
    Camera::height = height;
    Camera::Position = position;
}
