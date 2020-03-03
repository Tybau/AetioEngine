#pragma once

#include <GL/glew.h>

#include <iostream>

class Framebuffer
{
private:
	int width;
	int height;

	GLuint fbo;
	GLuint texture;
	GLuint depth_render_buffer;
public:
	Framebuffer(int width, int height);
	~Framebuffer();

	void bind();
    void unbind();
};