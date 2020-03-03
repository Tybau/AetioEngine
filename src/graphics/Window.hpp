#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT

#include <nuklear.h>
#include <nuklear_glfw_gl4.hpp>

#define MAX_VERTEX_BUFFER 512 * 1024
#define MAX_ELEMENT_BUFFER 128 * 1024

class Window
{
private:
    int                     width;
    int                     height;
    std::string             title;

    GLFWwindow              *window;
    struct nk_context       *nk;
    struct nk_font_atlas    *atlas;
    struct nk_colorf        color;
public:
    Window(int w, int h, std::string t);
    ~Window();

    void update();
    void clear();

    bool closeRequested();

    int getWidth() { return width; }
    int getHeight() { return height; }

    GLFWwindow *getWindow() { return window; }
    struct nk_context *getNkContext() { return nk; }
    struct nk_colorf getColor() { return color; }
    struct nk_colorf setColor(struct nk_colorf c) { color.r = c.r, color.g = c.g, color.b = c.b; }
};
