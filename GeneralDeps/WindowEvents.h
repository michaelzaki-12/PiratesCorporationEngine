//
// Created by pirates on 02/02/24.
//

#ifndef PIRATESENGINE_WINDOWEVENTS_H
#define PIRATESENGINE_WINDOWEVENTS_H

#include "EventSystem.h"
class WindowEvents : public EventSystem {
public:
    int width, height;
    virtual ~WindowEvents() = default;
    void OnUpdate(GLFWwindow* window) override;
    void UpdateFrameBuffer(GLFWwindow* window, int width_in_pixels, int height_in_Pixels) override;
private:
//    bool window_resized = false;
};


#endif //PIRATESENGINE_WINDOWEVENTS_H
