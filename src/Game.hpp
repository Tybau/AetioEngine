#ifndef AETIOENGINE_GAME_HPP
#define AETIOENGINE_GAME_HPP


#include <graphics/Window.hpp>
#include <graphics/Mesh.hpp>
#include <graphics/Shader.hpp>

#include <glm/gtc/matrix_transform.hpp>

class Game
{
private:
    Mesh *mesh;
    Shader *shader;
    glm::mat4 projectionMatrix;
    glm::mat4 transformationMatrix;
public:
    Game();
    ~Game();

    void update();
    void render(Window *window);
    void renderGUI(Window *window);
};


#endif //AETIOENGINE_GAME_HPP
