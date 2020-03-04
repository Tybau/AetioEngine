#pragma once

#include <graphics/Window.hpp>
#include <graphics/Mesh.hpp>
#include <graphics/Shader.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include <utils/Input.hpp>

#include <time.h>

struct bitmap_thread
{
	bool alive;
	unsigned char *image_data;

	int width;
	int height;
};

class Context
{
private:
    Mesh *mesh;
    Shader *shader;
    glm::mat4 projectionMatrix;
    glm::mat4 transformationMatrix;
    glm::mat4 viewMatrix;

    glm::vec3 pos;
    glm::vec3 rot;

	// image save
	clock_t timer;
	pthread_t thread;
	bitmap_thread thread_data;
public:
    Context();
    ~Context();

    void update(Input input);
    void render(Window *window);
    void renderGUI(Window *window);
};
