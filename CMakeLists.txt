cmake_minimum_required(VERSION 3.26)
project(rube_cub)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(lib)
add_executable(${PROJECT_NAME} main.cpp
        window.cpp
        window.h
        events.cpp
        events.h
        Shader.cpp
        Shader.h
        Texture.cpp
        Texture.h
        Camera.cpp
        Camera.h
)

target_link_libraries(${PROJECT_NAME}
        glfw ${OPENGL_glu_LIBRARY} ${GLFW_LIBRARIES}
        libglew_static
        glm::glm
        glad
)

target_include_directories(${PROJECT_NAME} PUBLIC
        ${GLEW_INCLUDES}
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/glad/include
)