//
// Created by pirates on 29/09/23.
//
#pragma once
#ifndef PIRATESENGINE_VERTEXBUFFER_H
#define PIRATESENGINE_VERTEXBUFFER_H
#include "glad/glad.h"

class VertexBufferObject{
public:
    GLuint ID;
    VertexBufferObject(GLfloat* Vertices, GLsizeiptr size);


    void Bind();
    void UnBind();
    void Delete();
};


#endif //PIRATESENGINE_VERTEXBUFFER_H
