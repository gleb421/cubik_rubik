#include <iostream>

#include "Camera.h"
#include "GL/glew.h"
#include <GLFW/glfw3.h>
#include "window.h"
#include "events.h"
#include "Shader.h"
#include "glm/glm.hpp"
#include "glm/ext.hpp"

using namespace std;
using namespace glm;
float vertices[] = {
        0.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f};

int main(void) {
    Window::initialize(Window::width, Window::height, "name");
    Events::initialize();
    glClearColor(0, 0, 1, 1);
    Shader *shader = load_shader("../main.glslv", "../main.glslf");
    if (shader == nullptr) {
        std::cerr << "FAIL" << std::endl;
        return 1;
    }
    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *) (0 * sizeof(GLfloat)));
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
    glClearColor(0.6f, 0.62f, 0.65f, 1);
    glm::mat4 model(1.0f);
    model = glm::translate(model, glm::vec3(0.5f, 0, 0));
    Camera *camera = new Camera(vec3(0.0f, 0, 1.0f), radians(40.0f));
    float lastTime = glfwGetTime();
    float delta = 0;
    float camX = 0;
    float camY = 0;
    while (!Window::isShouldClose()) {
        float currentTime = glfwGetTime();
        delta = currentTime - lastTime;
        lastTime = currentTime;


        Events::pullEvents();
        if (Events::jpressed(GLFW_KEY_ESCAPE)) {
            Window::setShouldClose(1);
        }
        if (Events::jclicked(GLFW_MOUSE_BUTTON_1)) {
            glClearColor(0.8f, 0.4f, 0.62f, 1);
        }
        float speed = 10;
        if (Events::jpressed(GLFW_KEY_TAB)) {
            Events::toogleCursor();
        }
        if (Events::jpressed(GLFW_KEY_S)) {
            camera->position -= camera->front * delta * speed;
        }
        if (Events::jpressed(GLFW_KEY_W)) {
            camera->position += camera->front * delta * speed;
        }
        if (Events::jpressed(GLFW_KEY_A)) {
            camera->position -= camera->right * delta * speed;
        }
        if (Events::jpressed(GLFW_KEY_D)) {
            camera->position += camera->right * delta * speed;
        }
        if (Events::_cursor_locked){
            camY += -Events::deltaY / Window::height * 2;
            camX += -Events::deltaX / Window::height * 2;

            if (camY < -radians(89.0f)){
                camY = -radians(89.0f);
            }
            if (camY > radians(89.0f)){
                camY = radians(89.0f);
            }

            camera->rotation = mat4(1.0f);
            camera->rotate(camY, camX, 0);
        }
        glClear(GL_COLOR_BUFFER_BIT);
        shader->use();
        shader->uniformMatrix("model", model);
        shader->uniformMatrix("projview", camera->getProjection() * camera->getView());

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);
        Window::swapBuffers();
    }
//
    Window::terminate();
    return 0;
}