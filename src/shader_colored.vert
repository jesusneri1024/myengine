#version 410 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 FragPos;
out vec3 Normal;

uniform mat4 transform;
uniform mat4 view;
uniform mat4 projection;

void main() {
    vec4 worldPosition = transform * vec4(aPos, 1.0);
    FragPos = vec3(worldPosition);
    Normal = mat3(transpose(inverse(transform))) * aNormal;

    gl_Position = projection * view * worldPosition;
}
