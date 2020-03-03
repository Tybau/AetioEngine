cmake_minimum_required(VERSION 3.10)
project(AetioEngine)

set(NAME AetioEngine)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)
add_definitions(-DGLEW_STATIC)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(deps/glfw)

set(BUILD_UTILS OFF CACHE BOOL "" FORCE)
add_subdirectory(deps/glew/build/cmake)

include_directories(deps/glm)

set(SOURCES
        src/main.cpp
        src/graphics/Window.cpp
        src/graphics/Window.hpp
        src/Context.cpp src/Context.hpp
        src/graphics/Mesh.cpp
        src/graphics/Mesh.hpp
        src/graphics/Shader.cpp
		src/graphics/Shader.hpp
		src/graphics/Framebuffer.cpp
		src/graphics/Framebuffer.hpp
		src/utils/Buffer.hpp 
		src/utils/Input.cpp src/utils/Input.hpp
		src/utils/bitmap_image.hpp)

include_directories(src/ include/)
add_executable(${NAME} ${SOURCES})

target_include_directories(${NAME} PUBLIC ${OPENGL_INCLUDE_DIR} deps/glfw/include deps/glew/include)
target_link_libraries(${NAME} ${OPENGL_gl_LIBRARY} glfw glew)