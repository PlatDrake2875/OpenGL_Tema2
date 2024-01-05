// Shader-ul de varfuri / Vertex shader
#version 330 core
#extension GL_ARB_separate_shader_objects : enable

layout (location = 0) in vec3 in_Position;
layout (location = 1) in vec3 in_Normal;
layout (location = 2) in vec2 in_texCoords;

uniform mat4 projection;
uniform mat4 view;

out vec4 gl_Position; 
out vec4 ex_Color;
out vec2 texCoords;

vec4 inPosition = vec4(in_Position, 1.0);

void main ()
{
	gl_Position = projection * view * inPosition;
	texCoords = in_texCoords;
   // ex_Color = vec4(1.0f, 0.0f, 0.0f, 1.0f);
}