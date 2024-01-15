// Shader-ul de varfuri / Vertex shader
#version 330 core
#extension GL_ARB_separate_shader_objects : enable

layout (location = 0) in vec3 in_Position;
layout (location = 1) in vec3 in_Normal;
layout (location = 2) in vec2 in_texCoords;

out vec3 FragPos;
out vec3 Normal;
out vec3 inLightPos;
out vec3 inViewPos;
out vec3 dir;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

uniform mat4 matrUmbra;
uniform mat4 myMatrix;
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 lightColor;
uniform int codCol;

out vec4 gl_Position; 
out vec4 ex_Color;
out vec2 texCoords;

vec4 inPosition = vec4(in_Position, 1.0);

void main ()
{
	gl_Position = projection * view * model * inPosition;
	texCoords = in_texCoords;
    // ex_Color = vec4(1.0f, 0.0f, 0.0f, 1.0f);

    Normal =mat3(projection*view*myMatrix)*in_Normal; 
    inLightPos = vec3(projection*view*myMatrix* vec4(lightPos, 1.0f));
    inViewPos =vec3(projection*view*myMatrix*vec4(viewPos, 1.0f));
    dir = mat3(projection*view*myMatrix) * vec3(0.0,100.0,200.0); // pentru sursa directionala
    FragPos = vec3(gl_Position);


}