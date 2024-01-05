// Shader-ul de fragment / Fragment shader 
#version 330 core
#extension GL_ARB_separate_shader_objects : enable

out vec4 outColor;
in vec2 texCoords;

uniform sampler2D textureMap;

void main(void)
{
	outColor = texture(textureMap, texCoords);
}