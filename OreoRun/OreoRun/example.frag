#version 330 core

// Inputs from the vertex shader
in vec2 texCoords;
in vec3 FragPos;  
in vec3 Normal; 
in vec3 inLightPos;
in vec3 inViewPos;
in vec3 dir;
in vec3 ex_Color; 

// Output color
out vec4 out_Color;

// Uniforms
uniform sampler2D textureMap;
uniform vec3 lightColor;
uniform int codCol; 

void main(void)
{
    //if (codCol == 0) // Apply lighting
    //{
    // Texture color
    vec4 texColor = texture(textureMap, texCoords);

    // Ambient
    float ambientStrength = 0.2f;
    vec3 ambient = ambientStrength * lightColor;

    // Diffuse 
    vec3 normala = normalize(Normal);
    vec3 lightDir = normalize(inLightPos - FragPos);
    float diff = max(dot(normala, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // Specular
    float specularStrength = 0.5f;
    vec3 viewDir = normalize(inViewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, normala);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 1);
    vec3 specular = specularStrength * spec * lightColor;

    vec3 result = (ambient + diffuse + specular) * vec3(texColor);
    out_Color = vec4(result, texColor.a);
    /*}
    else if (codCol == 1) // Draw shadow
    {
        vec3 black = vec3(0.f, 0.f, 0.f);
        out_Color = vec4(black, 1.0);
    }*/
}
