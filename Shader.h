//
// Created by pirates on 29/09/23.
//

#ifndef PIRATESENGINE_SHADER_H
#define PIRATESENGINE_SHADER_H
#pragma once

#include "glad/glad.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>
#include <string>

std::string GetFileContent(const char* filename);
class Shader{
public:
    GLuint ID;
    Shader(const char* VertexFile, const char* FragFile);
    void Activate();
    void Delete();
private:
    void CompileErrors(unsigned int shader, const char* type);
};


#endif //PIRATESENGINE_SHADER_H
