#include <utils/Buffer.hpp>
#include "Mesh.hpp"

Mesh::Mesh(Buffer<GLfloat> positions, Buffer<GLfloat> colors, Buffer<GLuint> indices)
    : positions(positions), colors(colors), indices(indices)
{
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &cbo);
    glGenBuffers(1, &ibo);

    glBindVertexArray(vao);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, positions.getMemorySize(), positions.getBuffer(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, cbo);
    glBufferData(GL_ARRAY_BUFFER, colors.getMemorySize(), colors.getBuffer(), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, nullptr);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.getMemorySize(), indices.getBuffer(), GL_STATIC_DRAW);

    glBindVertexArray(0);
}

Mesh::~Mesh() {}

void Mesh::draw()
{
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, indices.getSize(), GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}