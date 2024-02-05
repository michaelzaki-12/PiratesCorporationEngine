//
// Created by pirates on 29/09/23.
//

#include "IndexBuffer.h"

IndexBufferObject::IndexBufferObject(GLuint *Indices, GLsizeiptr size) {
    glGenBuffers(1, &ID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, Indices, GL_STATIC_DRAW);
}

void IndexBufferObject::Bind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void IndexBufferObject::UnBind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBufferObject::Delete() {
    glDeleteBuffers(1, &ID);
}
