#version 330 core

layout (location = 0) in vec3 v_position;
layout (location = 1) in vec3 color;

out vec4 a_color;

uniform mat4 model;
uniform mat4 projview;

// Константы для изменения цвета
const float red_offset = 0.3;
const float green_offset = 0.8;
const float blue_offset = 0.8;

void main(){
    vec3 modified_color = vec3(color.r + red_offset, color.g + green_offset, color.b + blue_offset);

    a_color = vec4(modified_color, 1);
    gl_Position =  projview * model * vec4(v_position, 1.0);
}
