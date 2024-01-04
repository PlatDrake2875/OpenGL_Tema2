// Shader-ul de varfuri / Vertex shader
#version 330 core
#extension GL_ARB_separate_shader_objects : enable

layout (location = 0) in vec3 in_Position;
layout (location = 1) in vec3 in_Normal;
layout (location = 2) in vec3 in_texCoords;

out vec4 gl_Position; 
out vec4 ex_Color;

void main ()
{
   gl_Position = vec4(in_Position, 1.0);
   ex_Color = vec4(0.0);
}