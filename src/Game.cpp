#include <utils/Buffer.hpp>
#include "Game.hpp"


Game::Game()
{
    GLfloat positions[] = {
            0, 0, 0,
            1, 0, 0,
            1, 1, 0,
            0, 1, 0,

            0, 0, 1,
            1, 0, 1,
            1, 1, 1,
            0, 1, 1
    };

    GLfloat colors[] = {
            1.0f, 0.0f, 0.0f, 1.0f,
            1.0f, 1.0f, 0.0f, 1.0f,
            0.0f, 1.0f, 1.0f, 1.0f,
            0.0f, 0.0f, 1.0f, 1.0f,

            1.0f, 0.0f, 0.0f, 1.0f,
            1.0f, 1.0f, 0.0f, 1.0f,
            0.0f, 1.0f, 1.0f, 1.0f,
            0.0f, 0.0f, 1.0f, 1.0f
    };

    GLuint indices[] = {
            0, 1, 2, 0, 2, 3,
            4, 6, 5, 4, 7, 6,

            0, 3, 4, 3, 7, 4,
            1, 5, 2, 2, 5, 6,
    };

    Buffer<GLfloat> pBuffer(positions, sizeof(positions));
    Buffer<GLfloat> cBuffer(colors, sizeof(colors));
    Buffer<GLuint> iBuffer(indices, sizeof(indices));

    mesh = new Mesh(pBuffer, cBuffer, iBuffer);

    shader = new Shader("../res/shaders/main.vert", "../res/shaders/main.frag");

    projectionMatrix = glm::perspective(glm::radians(45.0f), 1280.0f / 720.0f, 0.1f, 100.0f);

    transformationMatrix = glm::mat4(1.0f);
    transformationMatrix = glm::translate(transformationMatrix, glm::vec3(-1, 0, -5));
    transformationMatrix = glm::rotate(transformationMatrix, (glm::lowp_float)glm::radians(45.0), glm::vec3(0, 1, 0));
}

Game::~Game() { }

void Game::update()
{

}

void Game::render(Window *window)
{

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glEnable(GL_ALPHA_TEST);
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    shader->bind();

    shader->setUniform("projectionMatrix", projectionMatrix);
    shader->setUniform("transformationMatrix", transformationMatrix);

    mesh->draw();
    shader->unbind();
}

void Game::renderGUI(Window *window)
{
    struct nk_context *ctx = window->getNkContext();
    struct nk_colorf bg = window->getColor();

    /* GUI */
    if (nk_begin(ctx, "Demo", nk_rect(50, 50, 230, 250),
                 NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_SCALABLE|
                 NK_WINDOW_MINIMIZABLE|NK_WINDOW_TITLE))
    {
        enum {EASY, HARD};
        static int op = EASY;
        static int property = 20;
        nk_layout_row_static(ctx, 30, 80, 1);
        if (nk_button_label(ctx, "button"))
            fprintf(stdout, "button pressed\n");

        nk_layout_row_dynamic(ctx, 30, 2);
        if (nk_option_label(ctx, "easy", op == EASY)) op = EASY;
        if (nk_option_label(ctx, "hard", op == HARD)) op = HARD;

        nk_layout_row_dynamic(ctx, 25, 1);
        nk_property_int(ctx, "Compression:", 0, &property, 100, 10, 1);

        nk_layout_row_dynamic(ctx, 20, 1);
        nk_label(ctx, "background:", NK_TEXT_LEFT);
        nk_layout_row_dynamic(ctx, 25, 1);
        if (nk_combo_begin_color(ctx, nk_rgb_cf(window->getColor()), nk_vec2(nk_widget_width(ctx),400))) {
            nk_layout_row_dynamic(ctx, 120, 1);
            bg = nk_color_picker(ctx, bg, NK_RGBA);
            nk_layout_row_dynamic(ctx, 25, 1);
            bg.r = nk_propertyf(ctx, "#R:", 0, bg.r, 1.0f, 0.01f,0.005f);
            bg.g = nk_propertyf(ctx, "#G:", 0, bg.g, 1.0f, 0.01f,0.005f);
            bg.b = nk_propertyf(ctx, "#B:", 0, bg.b, 1.0f, 0.01f,0.005f);
            bg.a = nk_propertyf(ctx, "#A:", 0, bg.a, 1.0f, 0.01f,0.005f);
            nk_combo_end(ctx);
        }
    }
    nk_end(ctx);

    window->setColor(bg);
}