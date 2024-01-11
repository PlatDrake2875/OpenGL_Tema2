#version 330 core

// Uniforms
uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

// Vertex attributes
layout (location = 0) in vec3 in_Position;
layout (location = 1) in vec3 in_Normal;
layout (location = 2) in vec2 in_texCoords;

// Outputs to the fragment shader
out vec2 texCoords;

void main() {
    // Apply the transformations
    gl_Position = projection * view * model * vec4(in_Position, 1.0);
    texCoords = in_texCoords;
}
