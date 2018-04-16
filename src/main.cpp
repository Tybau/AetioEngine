#include <graphics/Window.hpp>
#include "Game.hpp"

int main()
{
    Window *window = new Window(1280, 720, "Hello!");

    Game game;

    while (!window->closeRequested())
    {
        game.update();

        window->clear();

        game.render(window);
        game.renderGUI(window);

        window->update();
    }

    delete window;

    return 0;
}