//
// Created by pirates on 05/02/24.
//

#ifndef PIRATESENGINE_OPENGLFRAMEBUFFER_H
#define PIRATESENGINE_OPENGLFRAMEBUFFER_H
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>

class OpenGLFrameBuffer {
public:
    ~OpenGLFrameBuffer();
    GLuint FBO = 0;
    GLuint RBO;
    GLuint TEXID;
    void GenerateFrameBuffer(int Width, int Height);
    void Bind();
    void UNBind();
    void Scale(int Width, int Height);

};


#endif //PIRATESENGINE_OPENGLFRAMEBUFFER_H
