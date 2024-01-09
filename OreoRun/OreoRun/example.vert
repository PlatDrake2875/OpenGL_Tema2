#version 330 core

layout (location = 0) in vec3 in_Position;
layout (location = 1) in vec3 in_Normal;
layout (location = 2) in vec2 in_texCoords;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model; // Model matrix for transformations

out vec2 texCoords;

void main() {
    texCoords = in_texCoords;
    gl_Position = projection * view * model * vec4(in_Position, 1.0);
}
