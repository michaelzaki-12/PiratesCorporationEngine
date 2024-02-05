//
// Created by pirates on 29/09/23.
//
#pragma once
#ifndef PIRATESENGINE_INDEXBUFFER_H
#define PIRATESENGINE_INDEXBUFFER_H
#include "glad/glad.h"

class IndexBufferObject{
public:
    GLuint ID;
    IndexBufferObject(GLuint* Indices, GLsizeiptr size);


    void Bind();
    void UnBind();
    void Delete();
};


#endif //PIRATESENGINE_INDEXBUFFER_H
