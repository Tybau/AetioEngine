#include <utils/Buffer.hpp>
#include "utils/bitmap_image.hpp"

#include "Context.hpp"

#include <fstream>
#include <pthread.h>
#include <turbojpeg.h>


Context::Context()
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
            0.0f, 1.0f, 0.0f, 1.0f,
            0.0f, 1.0f, 1.0f, 1.0f,

            1.0f, 1.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 1.0f, 1.0f,
            1.0f, 0.0f, 1.0f, 1.0f,
            0.0f, 1.0f, 1.0f, 1.0f
    };

    GLuint indices[] = {
            0, 1, 2, 0, 2, 3,
            4, 6, 5, 4, 7, 6,

            0, 3, 4, 3, 7, 4,
            1, 5, 2, 2, 5, 6,

            0, 4, 1, 1, 4, 5,
            2, 6, 3, 3, 6, 7
    };

    Buffer<GLfloat> pBuffer(positions, sizeof(positions));
    Buffer<GLfloat> cBuffer(colors, sizeof(colors));
    Buffer<GLuint> iBuffer(indices, sizeof(indices));

    mesh = new Mesh(pBuffer, cBuffer, iBuffer);

    shader = new Shader("../res/shaders/main.vert", "../res/shaders/main.frag");

    projectionMatrix = glm::perspective(glm::radians(45.0f), 1280.0f / 720.0f, 0.1f, 100.0f);

    transformationMatrix = glm::mat4(1.0f);
    transformationMatrix = glm::translate(transformationMatrix, glm::vec3(0, 0, -5));
    transformationMatrix = glm::rotate(transformationMatrix, (glm::lowp_float)glm::radians(15.0), glm::vec3(0, 0, 1));

	timer = clock();
	thread = 0;

	thread_data.alive = false;
	thread_data.image_data = (unsigned char *)malloc((int)(1280*720*3));
}

Context::~Context() 
{
	free(thread_data.image_data);
}

void Context::update(Input input)
{
    double speed = 0.1f;

    rot.x += input.getDY() * 0.002;
    rot.y += input.getDX() * 0.002;

    if(input.getKey(GLFW_KEY_W))
    {
        pos.z -= speed * cos(rot.y);
        pos.x += speed * sin(rot.y);
    }
    if(input.getKey(GLFW_KEY_A))
    {
        pos.z -= speed * sin(rot.y);
        pos.x -= speed * cos(rot.y);
    }
    if(input.getKey(GLFW_KEY_S))
    {
        pos.z += speed * cos(rot.y);
        pos.x -= speed * sin(rot.y);
    }
    if(input.getKey(GLFW_KEY_D))
    {
        pos.z += speed * sin(rot.y);
        pos.x += speed * cos(rot.y);
    }
    if(input.getKey(GLFW_KEY_LEFT_SHIFT))
        pos.y -= speed;
    if(input.getKey(GLFW_KEY_SPACE))
        pos.y += speed;

    viewMatrix = glm::mat4(1.0);
    viewMatrix = glm::rotate(viewMatrix, (glm::lowp_float)rot.y, glm::vec3(0, 1, 0));
    viewMatrix = glm::rotate(viewMatrix, (glm::lowp_float)rot.x , glm::normalize(glm::vec3(cos(-rot.y), 0, -sin(-rot.y))));
    viewMatrix = glm::translate(viewMatrix, -pos);
}

void *save_bitmap(void *data)
{
	bitmap_thread *thread_data = (bitmap_thread *)data;
	
	bitmap_image img(thread_data->width, thread_data->height);

	for(int i = 0; i < thread_data->height; i++)
	{
		for(int j = 0; j < thread_data->width; j++)
		{
			img.set_pixel(j, i, 
				thread_data->image_data[(i * thread_data->width + j) * 3 + 0],
				thread_data->image_data[(i * thread_data->width + j) * 3 + 1],
				thread_data->image_data[(i * thread_data->width + j) * 3 + 2]);
		}
	}
	img.save_image("test.bmp");

	thread_data->alive = false;
	pthread_exit(NULL);
}

void *save_jpg(void *data)
{
	bitmap_thread *thread_data = (bitmap_thread *)data;

	const int JPEG_QUALITY = 75;
	const int COLOR_COMPONENTS = 3;
	int _width = thread_data->width;
	int _height = thread_data->height;

	long unsigned int _jpegSize = 0;
	unsigned char* _compressedImage = NULL;

	tjhandle _jpegCompressor = tjInitCompress();

	tjCompress2(_jpegCompressor, thread_data->image_data, _width, 0, _height, TJPF_RGB,
			&_compressedImage, &_jpegSize, TJSAMP_444, JPEG_QUALITY,
			TJFLAG_FASTDCT);

	std::ofstream file;
	file.open("test.jpg");
	file.write((const char *)_compressedImage, _jpegSize);
	file.close();

	tjDestroy(_jpegCompressor);
	tjFree(_compressedImage);

	thread_data->alive = false;
	pthread_exit(NULL);
}

void Context::render(Window *window)
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glEnable(GL_ALPHA_TEST);
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    shader->bind();

    shader->setUniform("projectionMatrix", projectionMatrix);
    shader->setUniform("viewMatrix", viewMatrix);
    shader->setUniform("transformationMatrix", transformationMatrix);

    mesh->draw();
    shader->unbind();


	/**
	 * Generate image 10 fps
	 */
	
	if(thread_data.alive || ((double)clock() - (double)timer) / CLOCKS_PER_SEC < 1.0 / 50.0)
		return;
	timer = clock();
	
	glReadPixels(0, 0, window->getWidth(), window->getHeight(), GL_RGB, GL_UNSIGNED_BYTE, thread_data.image_data);

	thread_data.width = window->getWidth();
	thread_data.height = window->getHeight();
	thread_data.alive = true;
	pthread_create(&thread, NULL, save_jpg, (void *)&thread_data);	
}

void Context::renderGUI(Window *window)
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