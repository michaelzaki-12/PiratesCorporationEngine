//
// Created by pirates on 29/09/23.
//

#include "VertexArrayBuffer.h"

VertexArrayObject::VertexArrayObject() {
    glGenVertexArrays(1, &ID);
}

void VertexArrayObject::LinkVBO(VertexBufferObject VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset) {
    VBO.Bind();
    glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
    glEnableVertexAttribArray(layout);
    VBO.UnBind();

}

void VertexArrayObject::Bind() {
    glBindVertexArray(ID);
}

void VertexArrayObject::UnBind() {
    glBindVertexArray(0);
}

void VertexArrayObject::Delete() {
    glDeleteVertexArrays(1, &ID);
}
