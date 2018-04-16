#define NK_IMPLEMENTATION
#define NK_GLFW_GL4_IMPLEMENTATION
#include "Window.hpp"

Window::Window(int w, int h, std::string t)
{
    this->width = w;
    this->height = h;
    this->title = t;
    /* Initialize the library */
    if (!glfwInit())
        throw;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        throw;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwGetWindowSize(window, &width, &height);

    /* OpenGL */
    glViewport(0, 0, width, height);
    glewExperimental = 1;
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to setup GLEW\n");
        exit(1);
    }

    nk = nk_glfw3_init(window, NK_GLFW3_INSTALL_CALLBACKS, MAX_VERTEX_BUFFER, MAX_ELEMENT_BUFFER);

    nk_glfw3_font_stash_begin(&atlas);
    /*struct nk_font *roboto = nk_font_atlas_add_from_file(atlas, "../../../extra_font/Roboto-Regular.ttf", 14, 0);*/
    nk_glfw3_font_stash_end();

    color.r = 0.10f;
    color.g = 0.18f;
    color.b = 0.24f;
    color.a = 1.0f;
}

Window::~Window()
{
    nk_glfw3_shutdown();

    glfwTerminate();
}

bool Window::closeRequested()
{
    return (bool) glfwWindowShouldClose(window);
}

void Window::update()
{
    /* nk render */
    nk_glfw3_render(NK_ANTI_ALIASING_ON);

    /* Swap front and back buffers */
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();
}

void Window::clear()
{
    nk_glfw3_new_frame();

    glfwGetWindowSize(window, &width, &height);
    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(color.r, color.g, color.b, color.a);
}