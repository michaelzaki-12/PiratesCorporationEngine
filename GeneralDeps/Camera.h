//
// Created by pirates on 01/02/24.
//

#ifndef PIRATESENGINE_CAMERA_H
#define PIRATESENGINE_CAMERA_H
#define GLM_ENABLE_EXPERIMENTAL
#include "../imgui-docking/imgui.h"
#include "../imgui-docking/backends/imgui_impl_glfw.h"
#include "../imgui-docking/backends/imgui_impl_opengl3.h"
#include "../glad/glad.h"
#include "../glm-master/glm/glm.hpp"
#include "../glm-master/glm/gtc/matrix_transform.hpp"
#include "../glm-master/glm/gtc/type_ptr.hpp"
#include "../glm-master/glm/gtx/rotate_vector.hpp"
#include "../glm-master/glm/gtx/vector_angle.hpp"
#include "../Shader.h"
#include <GLFW/glfw3.h>


class Camera {
public:
    glm::vec3 Position;
    glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 UP = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::mat4 CameraMat = glm::mat4(1.0f);
    // Prevents the camera from jumping around when first clicking left click
    bool firstClick = true;
    int width, height;
    float speed = 0.1f, sensitivity = 10.0f;

    Camera(int width, int height, glm::vec3 position);
    void UpdateCamera(int width, int height, glm::vec3 position);
    void UpdateMatrix(float Fovdeg, float nearplane, float farplane);
    void Matrix(Shader& shader, const char* uniform);
    void Inputs(GLFWwindow* window);
};
#endif //PIRATESENGINE_CAMERA_H
