//
// Created by pirates on 29/09/23.
//

#ifndef PIRATESENGINE_VERTEXARRAYBUFFER_H
#define PIRATESENGINE_VERTEXARRAYBUFFER_H
#include "glad/glad.h"
#include "VertexBuffer.h"
class VertexArrayObject{
public:
    GLuint ID;
    VertexArrayObject();

    void LinkVBO(VertexBufferObject VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
    void Bind();
    void UnBind();
    void Delete();
};


#endif //PIRATESENGINE_VERTEXARRAYBUFFER_H
