// Shader-ul de fragment / Fragment shader 
#version 330 core
#extension GL_ARB_separate_shader_objects : enable

in vec4 ex_Color;
out vec4 out_Color;

void main(void)
{
	out_Color = ex_Color;
}