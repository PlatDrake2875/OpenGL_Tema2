#ifndef PLANE_H
#define PLANE_H

#include <glm/ext/vector_float4.hpp>
#include <glm/ext/matrix_float4x4.hpp>

struct PlaneVertex {
	glm::vec4 position;
	glm::vec3 color;
	glm::vec3 normal;
	glm::vec2 texCoord;

public:
	PlaneVertex()
		: position(0.0f, 0.0f, 0.0f, 0.0f),
		color(0.0f, 0.0f, 0.0f),
		normal(0.0f, 0.0f, 0.0f),
		texCoord(0.0f, 0.0f) {}
	
	PlaneVertex(const glm::vec4& pos, const glm::vec3& col, const glm::vec3& norm, const glm::vec2& tex)
		: position(pos), color(col), normal(norm), texCoord(tex) {}
};

class Plane
{
	PlaneVertex vertices[4];  
	unsigned int VAO, VBO, EBO;
public:
	float A, B, C, D; // ax + by + cz + d = 0
	                  // Creeaza plan (DREPTUNGHI) cu 4 puncte date (aveti grija ca punctele sa fie coplanare si sa fie intr-o ordine CONVEXA)
	Plane()
		: vertices{
			PlaneVertex(glm::vec4(0.0f), glm::vec3(0.0f), glm::vec3(0.0f), glm::vec2(0.0f)),
			PlaneVertex(glm::vec4(0.0f), glm::vec3(0.0f), glm::vec3(0.0f), glm::vec2(0.0f)),
			PlaneVertex(glm::vec4(0.0f), glm::vec3(0.0f), glm::vec3(0.0f), glm::vec2(0.0f)),
			PlaneVertex(glm::vec4(0.0f), glm::vec3(0.0f), glm::vec3(0.0f), glm::vec2(0.0f))
		},
		VAO(0), VBO(0), EBO(0), A(0.0f), B(0.0f), C(0.0f), D(0.0f)
	{
		// Additional initialization as needed
	}
	Plane(const PlaneVertex& v1, const PlaneVertex& v2, const PlaneVertex& v3, const PlaneVertex& v4);
	void Compute_Coeffs();
	void setupPlane();  // Method to load the plane into OpenGL
	glm::mat4 computeShadowMatrix(glm::vec4 lightSource, float D = -0.2f);
};


#endif // !PLANE_H



