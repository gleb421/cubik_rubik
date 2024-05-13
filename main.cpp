#include <iostream>

#include "Camera.h"
#include "GL/glew.h"
#include <GLFW/glfw3.h>
#include "window.h"
#include "events.h"
#include "Shader.h"
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include <ctime>
#include <cstdlib>

using namespace std;
using namespace glm;
static GLfloat vertices[] = {-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1, 0, 0,
                             0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1, 0, 0,
                             0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1, 0, 0,
                             0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1, 0, 0,
                             -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 1, 0, 0,
                             -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1, 0, 0,


                             -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0, 1, 0,
                             0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0, 1, 0,
                             0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 0, 1, 0,
                             0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 0, 1, 0,
                             -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0, 1, 0,
                             -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0, 1, 0,

                             -0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0, 0, 1,
                             -0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0, 0, 1,
                             -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0, 0, 1,
                             -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0, 0, 1,
                             -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0, 0, 1,
                             -0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0, 0, 1,


                             0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.25f, 0.5f, 1,
                             0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.25f, 0.5f, 1,
                             0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.25f, 0.5f, 1,
                             0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.25f, 0.5f, 1,
                             0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.25f, 0.5f, 1,
                             0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.25f, 0.5f, 1,

                             -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.52f, 0, 1,
                             0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.52f, 0, 1,
                             0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.52f, 0, 1,
                             0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.52f, 0, 1,
                             -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.52f, 0, 1,
                             -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.52f, 0, 1,

                             -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 1, 0.155f, 1,
                             0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1, 0.155f, 1,
                             0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 1, 0.155f, 1,
                             0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 1, 0.155f, 1,
                             -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1, 0.155f, 1,
                             -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 1, 0.155f, 1,
};

class Kubic {
public:

    glm::vec3 offset;
    glm::vec3 vec_x = {1.0f, 0.0f, 0.0f};
    glm::vec3 vec_y = {0.0f, 1.0f, 0.0f};
    glm::vec3 vec_z = {0.0f, 0.0f, 1.0f};
    glm::mat3 norm;
    glm::mat4 model;
    GLuint VAO, VBO;
    int number = 0;

    void initialize() {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        // position
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *) (0 * sizeof(GLfloat)));
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *) (5 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);

        glBindVertexArray(0);
    }

    void draw() {
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
    }

public:
    Kubic() {
        model = glm::mat4(1.0f);
        initialize();
    }

    void del_Kubic() {
        glDeleteBuffers(1, &VBO);
        glDeleteVertexArrays(1, &VAO);
    }


    Kubic(glm::vec3 off) {
        offset = off;
        model = glm::mat4(1.0f);
        model = glm::translate(model, offset);
        initialize();
    }

    void rotate(glm::vec3 rotate) {
        model = glm::rotate(model, radians(1.0f), glm::mat3(vec_x, vec_y, vec_z) * rotate);
    }

    void set_norm_up() {
        glm::vec3 buf = vec_y;
        vec_y = -vec_z;
        vec_z = buf;
    }

    void set_norm_down() {
        glm::vec3 buf = -vec_y;
        vec_y = vec_z;
        vec_z = buf;
    }

    void set_norm_front() {
        glm::vec3 buf = vec_x;
        vec_x = vec_z;
        vec_z = -buf;
    }

    void set_norm_back() {
        glm::vec3 buf = -vec_x;
        vec_x = -vec_z;
        vec_z = -buf;
    }

    void set_norm_right() {
        glm::vec3 buf = vec_y;
        vec_y = vec_x;
        vec_x = -buf;
    }

    void set_norm_left() {
        glm::vec3 buf = -vec_y;
        vec_y = -vec_x;
        vec_x = -buf;
    }

    void move(glm::vec3 rotate) {
        model = glm::translate(model, rotate);
    }


};

class Kubic_Rubica {
    std::vector<std::vector<std::vector<Kubic>>> vertices;
    Shader *shader;

    void rotateMatrixUp(std::vector<std::vector<Kubic>> &matrix) {
        int n = matrix.size();

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n / 2; j++) {
                std::swap(matrix[i][j], matrix[i][n - j - 1]);
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                std::swap(matrix[i][j], matrix[j][i]);
            }
        }
    }

    void rotateMatrixDown(std::vector<std::vector<Kubic>> &matrix) {
        int n = matrix.size();
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                std::swap(matrix[i][j], matrix[j][i]);
            }
        }
        // Меняем местами элементы на нижней половине матрицы с элементами на верхней половине
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n / 2; j++) {
                std::swap(matrix[i][j], matrix[i][n - j - 1]);
            }
        }
        // Меняем местами элементы на верхней половине матрицы с элементами на нижней половине

    }


    void rotateMatrixRight(std::vector<std::vector<std::vector<Kubic>>> &matrix, int z) {
        int n = matrix.size();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n / 2; j++) {
                std::swap(matrix[i][j][z], matrix[i][n - j - 1][z]);
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                std::swap(matrix[i][j][z], matrix[j][i][z]);
            }
        }
    }

    void rotateMatrixLeft(std::vector<std::vector<std::vector<Kubic>>> &matrix, int z) {
        int n = matrix.size();
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                std::swap(matrix[i][j][z], matrix[j][i][z]);
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n / 2; j++) {
                std::swap(matrix[i][j][z], matrix[i][n - j - 1][z]);
            }
        }

    }

    void rotateMatrixFront(std::vector<std::vector<std::vector<Kubic>>> &matrix, int y) {
        int n = matrix.size();


        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                std::swap(matrix[i][y][j], matrix[j][y][i]);
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n / 2; j++) {
                std::swap(matrix[i][y][j], matrix[i][y][n - j - 1]);
            }
        }
    }

    void rotateMatrixBack(std::vector<std::vector<std::vector<Kubic>>> &matrix, int y) {
        int n = matrix.size();

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n / 2; j++) {
                std::swap(matrix[i][y][j], matrix[i][y][n - j - 1]);
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                std::swap(matrix[i][y][j], matrix[j][y][i]);
            }
        }

    }

public:
    Kubic_Rubica() {
        for (int x = -1; x < 2; x++) {
            std::vector<std::vector<Kubic>> a1;
            for (int y = -1; y < 2; y++) {
                std::vector<Kubic> a2;
                for (int z = -1; z < 2; z++) {
                    a2.emplace_back(glm::vec3(x, y, z));
                }
                a1.push_back(a2);
            }
            vertices.push_back(a1);
        }
        for (int x = 0; x < 3; x++) {
            for (int y = 0; y < 3; y++) {
                for (int z = 0; z < 3; z++) {
                    vertices[x][y][z].number = (x * 9 + y * 3 + z);
                }
            }
        }
    }

    ~Kubic_Rubica() {
        for (int x = 0; x < 3; x++) {
            for (int y = 0; y < 3; y++) {
                for (int z = 0; z < 3; z++) {
                    vertices[x][y][z].del_Kubic();
                }
            }
        }
    }

    void draw(Shader *shader) {
        this->shader = shader;
        for (int x = 0; x < 3; x++) {
            for (int y = 0; y < 3; y++) {
                for (int z = 0; z < 3; z++) {
                    shader->uniformMatrix("model", vertices[x][y][z].model);
                    vertices[x][y][z].draw();
                }
            }
        }
    }

    void rotate_front(int y) {
        for (int i = 0; i < 90; i++) {
            for (int z = 0; z < 3; z++) {
                for (int x = 0; x < 3; x++) {
                    glm::vec3 off = vertices[x][y][z].offset;
                    vertices[x][y][z].move(-off);
                    vertices[x][y][z].rotate(glm::vec3(0, 1, 0));
                    vertices[x][y][z].move(off);
                    //*glm::vec3(1, 0,0)

                }
            }
            if (i % 15 == 0) {
                draw(shader);
                Window::swapBuffers();
            }
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        }
        for (int z = 0; z < 3; z++) {
            for (int x = 0; x < 3; x++) {
                vertices[x][y][z].set_norm_front();
                //*glm::vec3(1, 0,0)

            }
        }
        rotateMatrixFront(vertices, y);
    }

    void rotate_back(int y) {
        for (int i = 0; i < 90; i++) {
            for (int z = 0; z < 3; z++) {
                for (int x = 0; x < 3; x++) {
                    glm::vec3 off = vertices[x][y][z].offset;
                    vertices[x][y][z].move(-off);
                    vertices[x][y][z].rotate(glm::vec3(0, -1, 0));
                    vertices[x][y][z].move(off);
                    //*glm::vec3(1, 0,0)

                }
            }
            if (i % 15 == 0) {
                draw(shader);
                Window::swapBuffers();
            }
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        }
        for (int z = 0; z < 3; z++) {
            for (int x = 0; x < 3; x++) {
                vertices[x][y][z].set_norm_back();
                //*glm::vec3(1, 0,0)

            }
        }
        rotateMatrixBack(vertices, y);
    }

    void rotate_up(int x) {
        for (int i = 0; i < 90; i++) {
            for (int z = 0; z < 3; z++) {
                for (int y = 0; y < 3; y++) {
                    glm::vec3 off = vertices[x][y][z].offset;
                    vertices[x][y][z].move(-off);
                    vertices[x][y][z].rotate(glm::vec3(1, 0, 0));
                    vertices[x][y][z].move(off);
                    //*glm::vec3(1, 0,0)

                }
            }
            if (i % 15 == 0) {
                draw(shader);
                Window::swapBuffers();
            }
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        }
        for (int z = 0; z < 3; z++) {
            for (int y = 0; y < 3; y++) {
                vertices[x][y][z].set_norm_up();
                //*glm::vec3(1, 0,0)

            }
        }
        rotateMatrixUp(vertices[x]);
        //vertices[z] =  rotateMatrix(vertices[z]);
    }

    void rotate_down(int x) {
        for (int i = 0; i < 90; i++) {
            for (int z = 0; z < 3; z++) {
                for (int y = 0; y < 3; y++) {
                    glm::vec3 off = vertices[x][y][z].offset;
                    vertices[x][y][z].move(-off);
                    vertices[x][y][z].rotate(glm::vec3(-1, 0, 0));
                    vertices[x][y][z].move(off);
                    //*glm::vec3(1, 0,0)

                }
            }
            if (i % 15 == 0) {
                draw(shader);
                Window::swapBuffers();
            }
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        }
        for (int z = 0; z < 3; z++) {
            for (int y = 0; y < 3; y++) {
                vertices[x][y][z].set_norm_down();
                //*glm::vec3(1, 0,0)

            }
        }
        rotateMatrixDown(vertices[x]);
        //vertices[z] =  rotateMatrix(vertices[z]);
    }

    void rotate_right(int z) {
        for (int i = 0; i < 90; i++) {
            for (int y = 0; y < 3; y++) {
                for (int x = 0; x < 3; x++) {
                    glm::vec3 off = vertices[x][y][z].offset;
                    vertices[x][y][z].move(-off);
                    vertices[x][y][z].rotate(glm::vec3(0, 0, 1));
                    vertices[x][y][z].move(off);

                    //*glm::vec3(1, 0,0)

                }
            }
            if (i % 15 == 0) {
                draw(shader);
                Window::swapBuffers();
            }
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        }
        for (int x = 0; x < 3; x++) {
            for (int y = 0; y < 3; y++) {
                vertices[x][y][z].set_norm_right();
                //*glm::vec3(1, 0,0)

            }
        }

        rotateMatrixRight(vertices, z);

    }

    void rotate_left(int z) {
        for (int i = 0; i < 90; i++) {
            for (int y = 0; y < 3; y++) {
                for (int x = 0; x < 3; x++) {
                    glm::vec3 off = vertices[x][y][z].offset;
                    vertices[x][y][z].move(-off);
                    vertices[x][y][z].rotate(glm::vec3(0, 0, -1));
                    vertices[x][y][z].move(off);

                    //*glm::vec3(1, 0,0)

                }
            }
            if (i % 15 == 0) {
                draw(shader);
                Window::swapBuffers();
            }
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        }
        for (int x = 0; x < 3; x++) {
            for (int y = 0; y < 3; y++) {
                vertices[x][y][z].set_norm_left();
                //*glm::vec3(1, 0,0)

            }
        }

        rotateMatrixLeft(vertices, z);

    }
};

void disassembleCube(Kubic_Rubica &rube_cub, int *activities, int size) {
    for (int i = 0; i < size; ++i) {
        if (activities[i] == 0)rube_cub.rotate_up(0);
        else if (activities[i] == 1) rube_cub.rotate_up(1);
        else if (activities[i] == 2) rube_cub.rotate_up(2);
        else if (activities[i] == 3)rube_cub.rotate_front(0);
        else if (activities[i] == 4) rube_cub.rotate_front(1);
        else if (activities[i] == 5) rube_cub.rotate_front(2);
        else if (activities[i] == 6) rube_cub.rotate_right(0);
        else if (activities[i] == 7) rube_cub.rotate_right(1);
        else if (activities[i] == 8) rube_cub.rotate_right(2);
        else if (activities[i] == 9) rube_cub.rotate_down(0);
        else if (activities[i] == 10) rube_cub.rotate_down(1);
        else if (activities[i] == 11) rube_cub.rotate_down(2);
        else if (activities[i] == 12) rube_cub.rotate_back(0);
        else if (activities[i] == 13) rube_cub.rotate_back(1);
        else if (activities[i] == 14) rube_cub.rotate_back(2);
        else if (activities[i] == 15) rube_cub.rotate_left(0);
        else if (activities[i] == 16) rube_cub.rotate_left(1);
        else if (activities[i] == 17) rube_cub.rotate_left(2);

    }
}

void assembleCube(Kubic_Rubica &rube_cub, int *activities, int size) {
    for (int i = size - 1; i >= 0; --i) {
        if (activities[i] == 0) {
            rube_cub.rotate_down(0);
        } else if (activities[i] == 1) {
            rube_cub.rotate_down(1);
            rube_cub.rotate_right(2);
            rube_cub.rotate_down(2);
            rube_cub.rotate_up(2);
            rube_cub.rotate_left(2);
        } else if (activities[i] == 2) {
            rube_cub.rotate_down(2);
            rube_cub.rotate_left(1);
            rube_cub.rotate_front(2);
            rube_cub.rotate_back(2);
            rube_cub.rotate_right(1);
        } else if (activities[i] == 3) {
            rube_cub.rotate_back(0);
            rube_cub.rotate_down(2);
            rube_cub.rotate_back(0);
            rube_cub.rotate_front(0);
            rube_cub.rotate_up(2);
        } else if (activities[i] == 4) {
            rube_cub.rotate_back(1);
            rube_cub.rotate_front(1);
            rube_cub.rotate_back(1);
        } else if (activities[i] == 5) {
            rube_cub.rotate_back(2);

        } else if (activities[i] == 6) {
            rube_cub.rotate_left(0);
            rube_cub.rotate_right(2);
            rube_cub.rotate_down(2);
            rube_cub.rotate_up(2);
            rube_cub.rotate_left(2);
        } else if (activities[i] == 7) {
            rube_cub.rotate_left(1);

        } else if (activities[i] == 8) {
            rube_cub.rotate_left(2);

        } else if (activities[i] == 9) {
            rube_cub.rotate_up(0);

        } else if (activities[i] == 10) {
            rube_cub.rotate_up(1);
            rube_cub.rotate_right(1);
            rube_cub.rotate_left(1);
        } else if (activities[i] == 11) {
            rube_cub.rotate_up(2);
            rube_cub.rotate_front(1);
            rube_cub.rotate_back(1);
        } else if (activities[i] == 12) {
            rube_cub.rotate_front(0);
            rube_cub.rotate_left(1);
            rube_cub.rotate_front(2);
            rube_cub.rotate_back(2);
            rube_cub.rotate_right(1);
        } else if (activities[i] == 13) {
            rube_cub.rotate_front(1);
        } else if (activities[i] == 14) {
            rube_cub.rotate_front(2);
            rube_cub.rotate_right(1);
            rube_cub.rotate_left(1);
        } else if (activities[i] == 15) {
            rube_cub.rotate_right(0);
            rube_cub.rotate_right(2);
            rube_cub.rotate_down(2);
            rube_cub.rotate_up(2);
            rube_cub.rotate_left(2);
        } else if (activities[i] == 16) {
            rube_cub.rotate_right(1);
            rube_cub.rotate_front(1);
            rube_cub.rotate_back(1);
        } else if (activities[i] == 17) {
            rube_cub.rotate_right(2);
        }
    }

    // Инициализация массива случайными числами
    for (int i = 0; i < size; ++i) {
        activities[i] = rand() % 18;
    }
}

int main(void) {
    Window::initialize(Window::width, Window::height, "name");
    Events::initialize();
    int size = 50;
    int activities[size];

    // Инициализация массива случайными числами
    for (int i = 0; i < size; ++i) {
        activities[i] = rand() % 18;
    }
    glClearColor(0, 0, 1, 1);
    Shader *shader = load_shader("../main.glslv", "../main.glslf");
    if (shader == nullptr) {
        std::cerr << "FAIL" << std::endl;
        return 1;
    }

    glClearColor(0.7f, 0.62f, 0.65f, 1);
    Kubic_Rubica rube_cub = Kubic_Rubica();
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Camera *camera = new Camera(vec3(1.0f, 1.0f, 1.0f), radians(60.0f));
    float lastTime = glfwGetTime();
    float delta = 0.0f;
    float camX = 0;
    float camY = 0;
    glEnable(GL_DEPTH_TEST);
    int i = 0;
    bool fl_start = 0;
    camera->position -= camera->right * (float)5;
    camera->position -= camera->front *  (float)8;

    while (!Window::isShouldClose()) {
        float currentTime = glfwGetTime();
        delta = currentTime - lastTime;
        lastTime = currentTime;
        Events::pullEvents();
        float speed = 100;


        if (Events::jpressed(GLFW_KEY_N)) {
            disassembleCube(rube_cub, activities, size);
        }
        if (Events::jpressed(GLFW_KEY_M)) {
            assembleCube(rube_cub, activities, size);
        }
        if (Events::jpressed(GLFW_KEY_ESCAPE)) {
            Window::setShouldClose(1);
        }
        if (Events::jclicked(GLFW_MOUSE_BUTTON_1)) {
            glClearColor(0.8f, 0.4f, 0.62f, 1);
        }
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


        if ((Events::jpressed(GLFW_KEY_UP) && Events::pressed(GLFW_KEY_1))) {
            rube_cub.rotate_up(0);

        }
        if ((Events::jpressed(GLFW_KEY_UP) && Events::pressed(GLFW_KEY_2))) {
            rube_cub.rotate_up(1);

        }
        if ((Events::jpressed(GLFW_KEY_UP) && Events::pressed(GLFW_KEY_3))) {
            rube_cub.rotate_up(2);
        }


        if ((Events::jpressed(GLFW_KEY_DOWN) && Events::pressed(GLFW_KEY_1))) {
            rube_cub.rotate_down(0);

        }
        if ((Events::jpressed(GLFW_KEY_DOWN) && Events::pressed(GLFW_KEY_2))) {
            rube_cub.rotate_down(1);

        }
        if ((Events::jpressed(GLFW_KEY_DOWN) && Events::pressed(GLFW_KEY_3))) {
            rube_cub.rotate_down(2);
        }


        if ((Events::jpressed(GLFW_KEY_RIGHT) && Events::pressed(GLFW_KEY_1))) {
            rube_cub.rotate_right(0);
        }
        if ((Events::jpressed(GLFW_KEY_RIGHT) && Events::pressed(GLFW_KEY_2))) {
            rube_cub.rotate_right(1);
        }
        if ((Events::jpressed(GLFW_KEY_RIGHT) && Events::pressed(GLFW_KEY_3))) {
            rube_cub.rotate_right(2);
        }


        if ((Events::jpressed(GLFW_KEY_LEFT) && Events::pressed(GLFW_KEY_1))) {
            rube_cub.rotate_left(0);
        }
        if ((Events::jpressed(GLFW_KEY_LEFT) && Events::pressed(GLFW_KEY_2))) {
            rube_cub.rotate_left(1);
        }
        if ((Events::jpressed(GLFW_KEY_LEFT) && Events::pressed(GLFW_KEY_3))) {
            rube_cub.rotate_left(2);
        }


        if ((Events::jpressed(GLFW_KEY_X) && Events::pressed(GLFW_KEY_1))) {
            rube_cub.rotate_front(0);

        }
        if ((Events::jpressed(GLFW_KEY_X) && Events::pressed(GLFW_KEY_2))) {
            rube_cub.rotate_front(1);

        }
        if ((Events::jpressed(GLFW_KEY_X) && Events::pressed(GLFW_KEY_3))) {
            rube_cub.rotate_front(2);
        }


        if ((Events::jpressed(GLFW_KEY_Z) && Events::pressed(GLFW_KEY_1))) {
            rube_cub.rotate_back(0);

        }
        if ((Events::jpressed(GLFW_KEY_Z) && Events::pressed(GLFW_KEY_2))) {
            rube_cub.rotate_back(1);

        }
        if ((Events::jpressed(GLFW_KEY_Z) && Events::pressed(GLFW_KEY_3))) {
            rube_cub.rotate_back(2);
        }

        if (Events::_cursor_locked) {
            camY += -Events::deltaY / Window::height * 2;
            camX += -Events::deltaX / Window::height * 2;

            if (camY < -radians(89.0f)) {
                camY = -radians(89.0f);
            }
            if (camY > radians(89.0f)) {
                camY = radians(89.0f);
            }

            camera->rotation = mat4(1.0f);
            camera->rotate(camY, camX, 0);
        }
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shader->use();
        shader->uniformMatrix("projview", camera->getProjection() * camera->getView());
        rube_cub.draw(shader);
        i++;
        Window::swapBuffers();

    }
    delete shader;
    Window::terminate();
    return 0;
}
