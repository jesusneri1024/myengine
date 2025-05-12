#version 410 core
layout (location = 0) in vec3 aPos;

void main() {
    float w = 1; // <-- Cambia este valor para experimentar (1.0, 0.5, 2.0, etc.)
    gl_Position = vec4(aPos, w);
}
