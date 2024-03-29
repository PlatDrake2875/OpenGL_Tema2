#version 330 core

// Uniforms
uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

// Vertex attributes
layout (location = 0) in vec3 in_Position;
layout (location = 1) in vec3 in_Normal;
layout (location = 2) in vec2 in_texCoords;

out vec3 FragPos;
out vec3 Normal;
out vec3 inLightPos;
out vec3 inViewPos;
out vec3 dir;

uniform mat4 matrUmbra;
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 lightColor;


out vec4 gl_Position; 
out vec2 texCoords;

vec4 inPosition = vec4(in_Position, 1.0);
mat4 myMatrix = projection * view * model;


void main ()
{
	gl_Position = myMatrix * inPosition;
	texCoords = in_texCoords;

    Normal = mat3(myMatrix) * in_Normal; 
    inLightPos = vec3(myMatrix * vec4(lightPos, 1.0f));
    inViewPos =vec3(myMatrix*vec4(viewPos, 1.0f));
    dir = mat3(myMatrix) * vec3(0.0,100.0,200.0); // pentru sursa directionala
    FragPos = vec3(gl_Position);    
}
