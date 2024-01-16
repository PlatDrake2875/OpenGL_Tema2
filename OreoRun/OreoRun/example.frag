#version 330 core

// Inputs from the vertex shader
in vec2 texCoords;
in vec3 FragPos;  
in vec3 Normal; 
in vec3 inLightPos;
in vec3 inViewPos;
in vec3 dir;

// Output color
out vec4 out_Color;

// Uniforms
uniform sampler2D textureMap;
uniform vec3 lightColor;    
uniform vec4 objectColor;   // culoarea obiectului, daca nu are textura pusa
uniform int isLighted;  // 1 daca obiectul este luminat, 0 altfel
uniform int isLightSource;  // 1 daca obiectul este o sursa de lumina, 0 altfel
uniform int isTextured;     // 1 daca obiectul are textura pusa, 0 altfel

void main(void)
{
    vec4 usedColor;
    if(isTextured == 1)
        usedColor = texture(textureMap, texCoords);
    else
		usedColor = objectColor;

    
    if(isLighted == 1) {
        vec3 usedColor3 = vec3(usedColor);

        // Ambient
        float ambientStrength = 1.5f;
        vec3 ambient = ambientStrength * lightColor;
        vec3 ambient_term = ambient * usedColor3;

        // Diffuse 
        vec3 normala = normalize(Normal);
        vec3 lightDir = normalize(inLightPos - FragPos);
        float diff = max(dot(normala, lightDir), 0.0);
        vec3 diffuse = diff * lightColor * usedColor3;

        // Specular
        float specularStrength = 0.5f;
        float shininess = 100.0f;
        vec3 viewDir = normalize(inViewPos - FragPos);
        vec3 reflectDir = normalize(reflect(-lightDir, normala));
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
        vec3 specular_light = specularStrength  * lightColor;       //  specular_light=specularStrength  * lightColor;
        vec3 specular_term = spec * specular_light * usedColor3;

        vec3 emission = vec3(0, 0, 0);

        vec3 result = (ambient_term + diffuse + specular_term) * usedColor3;
        out_Color = vec4(result, usedColor.a);
    }
    else {
		out_Color = usedColor;
	}
}
