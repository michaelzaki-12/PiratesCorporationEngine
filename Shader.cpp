//
// Created by pirates on 29/09/23.
//

#include "Shader.h"

// Reads a text file and outputs a string with everything in the text file
std::string GetFileContent(const char* filename)
{
    std::ifstream in(filename, std::ios::binary);
    if (in)
    {
        std::string contents;
        in.seekg(0, std::ios::end);
        contents.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&contents[0], contents.size());
        in.close();
        return(contents);
    }
    throw(errno);
}

Shader::Shader(const char *VertexFile, const char *FragFile) {
    std::string vertexcode = GetFileContent(VertexFile);
    std::string fragcode = GetFileContent(FragFile);

    const char* vertexsource = vertexcode.c_str();
    const char* fragsource = fragcode.c_str();
    GLuint VertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(VertexShader, 1, &vertexsource, NULL);
    glCompileShader(VertexShader);
    CompileErrors(VertexShader, "VERTEX");

    GLuint FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(FragmentShader, 1, &fragsource, NULL);
    glCompileShader(FragmentShader);
    CompileErrors(FragmentShader, "FRAGMENT");

    ID =  glCreateProgram();
    glAttachShader(ID, VertexShader);
    glAttachShader(ID, FragmentShader);
    glLinkProgram(ID);
    CompileErrors(ID, "PROGRAM");
    // Delete the now useless Vertex and Fragment Shader objects
    glDeleteShader(VertexShader);
    glDeleteShader(FragmentShader);



}

void Shader::Activate() {
    glUseProgram(ID);
}
void Shader::Delete() {
    glDeleteProgram(ID);
}

void Shader::CompileErrors(unsigned int shader, const char *type) {
    GLint HasCompiled;
    char infoLog[1024];
    if ((std::string)type != "PROGRAM") {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &HasCompiled);
        if (HasCompiled == GL_FALSE) {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR SHADER_HAS_NOT_COMPILED " << type << "\n" << std::endl;
        }
    } else {
        glGetProgramiv(shader, GL_COMPILE_STATUS, &HasCompiled);
        if (HasCompiled == GL_FALSE) {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR SHADER_HAS_NOT_LINKED_CORRECTLY " << type << "\n" << std::endl;
        }

    }
}
