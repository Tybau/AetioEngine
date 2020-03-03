#pragma once

#include <GL/glew.h>
#include <utils/Buffer.hpp>

class Mesh
{
private:
    GLuint vao, vbo, cbo, ibo;

    Buffer<GLfloat> positions;
    Buffer<GLfloat> colors;
    Buffer<GLuint> indices;

public:
    Mesh(Buffer<GLfloat> positions, Buffer<GLfloat> colors, Buffer<GLuint> indices);
    ~Mesh();

    void draw();
};
