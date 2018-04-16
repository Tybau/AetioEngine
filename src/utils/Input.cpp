#include "Input.hpp"

Input::Input(Window *window)
    :  x(0), y(0), last_x(0), last_y(0), dx(0), dy(0), focused(0)
{
    this->window = window->getWindow();
}

Input::~Input() {}

void Input::update()
{
    if (glfwGetMouseButton(window, 0) && !focused)
    {
        focused = true;
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        glfwGetCursorPos(window, &last_x, &last_y);
    }
    else if (glfwGetKey(window, GLFW_KEY_ESCAPE) && window)
    {
        focused = false;
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
    if (focused) {
        glfwGetCursorPos(window, &x, &y);

        dx = x - last_x;
        dy = y - last_y;

        last_x = x;
        last_y = y;
    }
}

bool Input::getKey(int key)
{
    return glfwGetKey(window, key) == GLFW_PRESS;
}

bool Input::getButton(int button)
{
    return glfwGetMouseButton(window, button) == GLFW_KEY_ESCAPE;
}