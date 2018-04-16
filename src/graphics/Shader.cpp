#include "Shader.hpp"

Shader::Shader(const char *vertex_path, const char *fragment_path)
{
    std::ifstream vertex_file(vertex_path);
    std::ifstream fragment_file(fragment_path);

    std::string vertex_sources;
    std::string fragment_sources;

    std::string line;
    if(vertex_file.is_open())
        while(std::getline(vertex_file, line))
            vertex_sources += line + "\n";
    vertex_file.close();

    if(fragment_file.is_open())
        while(std::getline(fragment_file, line))
            fragment_sources += line + "\n";
    fragment_file.close();

    program = createProgram(vertex_sources.c_str(), fragment_sources.c_str());
}

Shader::~Shader() {}

GLuint Shader::createProgram(const char *vertex_sources, const char *fragment_sources)
{
    GLuint program = glCreateProgram();

    if(program == GL_FALSE) throw;

    GLuint vertex_shader = createShader(vertex_sources, GL_VERTEX_SHADER);
    glAttachShader(program, vertex_shader);

    GLuint fragment_shader = createShader(fragment_sources, GL_FRAGMENT_SHADER);
    glAttachShader(program, fragment_shader);

    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    return program;
}

GLuint Shader::createShader(const char *sources, GLenum type)
{
    GLuint shader = glCreateShader(type);
    GLint result;

    if(shader == GL_FALSE) throw;

    glShaderSource(shader, 1, &sources, nullptr);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &result);

    if(result == GL_FALSE)
    {
        GLint length;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
        char error[length];
        glGetShaderInfoLog(shader, length, &length, &error[0]);
        std::cout << &error[0] << std::endl;
        glDeleteShader(shader);
        return 0;
    }
    return shader;
}

GLint Shader::getUniformLocation(const char *name)
{
    return glGetUniformLocation(program, name);
}

void Shader::setUniform(const char *name, glm::mat4 mat)
{
    glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &mat[0][0]);
}

void Shader::bind()
{
    glUseProgram(program);
}

void Shader::unbind()
{
    glUseProgram(0);
}