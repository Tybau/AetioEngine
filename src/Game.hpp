#ifndef AETIOENGINE_GAME_HPP
#define AETIOENGINE_GAME_HPP


#include <graphics/Window.hpp>
#include <graphics/Mesh.hpp>
#include <graphics/Shader.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include <utils/Input.hpp>

class Game
{
private:
    Mesh *mesh;
    Shader *shader;
    glm::mat4 projectionMatrix;
    glm::mat4 transformationMatrix;
    glm::mat4 viewMatrix;

    glm::vec3 pos;
    glm::vec3 rot;
public:
    Game();
    ~Game();

    void update(Input input);
    void render(Window *window);
    void renderGUI(Window *window);
};


#endif //AETIOENGINE_GAME_HPP
