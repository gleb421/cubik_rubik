//
// Created by User on 09.05.2024.
//

#ifndef RUBE_CUB_CAMERA_H
#define RUBE_CUB_CAMERA_H
#include <glm/glm.hpp>
using namespace glm;

class Camera {
    void updateVectors();
public:
    vec3 front;
    vec3 up;
    vec3 right;

    vec3 position;
    float fov;
    mat4 rotation;
    Camera(vec3 position, float fov);

    void rotate(float x, float y, float z);

    mat4 getProjection();
    mat4 getView();
};


#endif //RUBE_CUB_CAMERA_H
