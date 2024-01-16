#version 330 core

// Inputs from the vertex shader
in vec2 texCoords;
in vec3 FragPos;  
in vec3 Normal; 
in vec3 inLightPos;
in vec3 inViewPos;
in vec3 dir;
in vec4 ex_Color; 

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
    vec3 texColor3 = vec3(texColor);

    // Ambient
    float ambientStrength = 0.8f;
    vec3 ambient = ambientStrength * lightColor;
    vec3 ambient_term = ambient * texColor3;

    // Diffuse 
    vec3 normala = normalize(Normal);
    vec3 lightDir = normalize(inLightPos - FragPos);
    float diff = max(dot(normala, lightDir), 0.0);
    vec3 diffuse = diff * lightColor * texColor3;

    // Specular
    float specularStrength = 0.5f;
    float shininess = 100.0f;
    vec3 viewDir = normalize(inViewPos - FragPos);
    vec3 reflectDir = normalize(reflect(-lightDir, normala));
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    vec3 specular_light = specularStrength  * lightColor;       //  specular_light=specularStrength  * lightColor;
    vec3 specular_term = spec * specular_light * texColor3;

    vec3 emission = vec3(0, 0, 0);

    vec3 result = (ambient_term + diffuse + specular_term) * texColor3;
    out_Color = vec4(result, texColor.a);
    /*}
    else if (codCol == 1) // Draw shadow
    {
        vec3 black = vec3(0.f, 0.f, 0.f);
        out_Color = vec4(black, 1.0);
    }*/
}
