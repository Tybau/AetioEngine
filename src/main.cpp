#include <graphics/Window.hpp>
#include <utils/Input.hpp>
#include "Context.hpp"

int main()
{
    Window *window = new Window(1280, 720, "Hello!");

    Input input(window);

    Game game;

    while (!window->closeRequested())
    {
        input.update();
        game.update(input);

        window->clear();

        game.render(window);
        game.renderGUI(window);

        window->update();
    }

    delete window;

    return 0;
}