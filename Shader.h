//
// Created by User on 09.05.2024.
//

#ifndef RUBE_CUB_SHADER_H
#define RUBE_CUB_SHADER_H
#include <string>
#include <glm/glm.hpp>

class Shader {
public:
    unsigned int id;

    Shader(unsigned int id);
    ~Shader();

    void use();
    void uniformMatrix(std::string  name, glm::mat4 matrix);
};

extern Shader* load_shader(std::string vertexFile, std::string fragmentFile);

#endif //RUBE_CUB_SHADER_H
