//
// Created by pirates on 29/09/23.
//

#include "VertexBuffer.h"


VertexBufferObject::VertexBufferObject(GLfloat *Vertices, GLsizeiptr size) {
    glGenBuffers(1, &ID);
    glBindBuffer(GL_ARRAY_BUFFER, ID);
    glBufferData(GL_ARRAY_BUFFER, size, Vertices, GL_STATIC_DRAW);

}

void VertexBufferObject::Bind() {
    glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VertexBufferObject::UnBind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBufferObject::Delete() {
    glDeleteBuffers(1, &ID);
}

