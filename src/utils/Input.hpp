#pragma once

#include <graphics/Window.hpp>
#include <GLFW/glfw3.h>

class Input
{
private:
    GLFWwindow *window;

    double x, y;
    double last_x, last_y;
    double dx, dy;
    bool focused = false;
public:
    Input(Window *window);
    ~Input();

    void update();

    bool getKey(int key);
    bool getButton(int button);

    double getX() { return x; }
    double getY() { return y; }
    double getDX() { return dx; }
    double getDY() { return dy; }
    bool isFocused() { return focused; }
    void setFocused(bool focused) { this->focused = focused; }
};
