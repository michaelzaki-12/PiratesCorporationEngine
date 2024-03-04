//
// Created by pirates on 06/10/23.
//
#pragma once
#ifndef PIRATESENGINE_TEXTURE_H
#define PIRATESENGINE_TEXTURE_H
#include "inc/stb_image.h"
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "Shader.h"
class Texture{
public:
    Texture(const char* image);
    static unsigned int LoadTexture(const char* image);
    void TextureRef(int Width, int Height, unsigned char* bytes);
    void Bind();
    void UnBind();
    void Delete();
    void DeleteLoadTexture(GLuint TEX);
    GLuint texture;
};

#endif //PIRATESENGINE_TEXTURE_H
