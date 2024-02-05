//
// Created by pirates on 02/02/24.
//

#ifndef PIRATESENGINE_EVENTSYSTEM_H
#define PIRATESENGINE_EVENTSYSTEM_H
#include <GLFW/glfw3.h>

class EventSystem {
public:
    virtual void OnUpdate(GLFWwindow* window) = 0;
    virtual void UpdateFrameBuffer(GLFWwindow* window, int width_in_pixels, int height_in_Pixels) = 0;
};


#endif //PIRATESENGINE_EVENTSYSTEM_H
