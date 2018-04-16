#ifndef AETIOENGINE_SHADER_HPP
#define AETIOENGINE_SHADER_HPP


#include <GL/glew.h>
#include <glm/glm.hpp>

#include <fstream>
#include <iostream>

class Shader
{
private:
    GLuint program;
public:
    Shader(const char *vertex_path, const char *fragment_path);
    ~Shader();

    GLuint createProgram(const char *vertex_sources, const char *fragment_sources);
    GLuint createShader(const char *sources, GLenum type);

    GLint getUniformLocation(const char *name);
    void setUniform(const char *name, glm::mat4 mat);

    void bind();
    void unbind();
};


#endif //AETIOENGINE_SHADER_HPP
