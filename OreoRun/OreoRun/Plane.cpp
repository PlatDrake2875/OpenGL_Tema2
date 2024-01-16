#include "Plane.h"
#include <GL/glew.h>


Plane::Plane(const PlaneVertex& v1, const PlaneVertex& v2, const PlaneVertex& v3, const PlaneVertex& v4)
{
	vertices[0] = v1;
	vertices[1] = v2;
	vertices[2] = v3;
	vertices[3] = v4;

	Compute_Coeffs();
	setupPlane();  
}

void Plane::Compute_Coeffs()
{
	auto& p1 = vertices[0].position;
	auto& p2 = vertices[1].position;
	auto& p3 = vertices[2].position;

	A = p1.y * p2.z + p2.y * p3.z + p3.y * p1.z -
		p3.y * p2.z - p1.y * p3.z - p2.y * p1.z;

	B = -(p1.x * p2.z + p2.x * p3.z + p3.x * p1.z -
		p3.x * p2.z - p1.x * p3.z - p2.x * p1.z);

	C = p1.x * p2.y + p2.x * p3.y + p3.x * p1.y -
		p3.x * p2.y - p1.x * p3.y - p2.x * p1.y;

	D = -(p1.x * p2.y * p3.z + p2.x * p3.y * p1.z +
		p3.x * p1.y * p2.z - p3.x * p2.y * p1.z -
		p1.x * p3.y * p2.z - p2.x * p1.y * p3.z);
}


void Plane::setupPlane() {
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	PlaneVertex vertices[] = {
		vertices[0], // Vertex 1
		vertices[1], // Vertex 2
		vertices[2], // Vertex 3
		vertices[3]  // Vertex 4
	};

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(PlaneVertex), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(PlaneVertex), (void*)offsetof(PlaneVertex, color));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(PlaneVertex), (void*)offsetof(PlaneVertex, normal));
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(PlaneVertex), (void*)offsetof(PlaneVertex, texCoord));
	glEnableVertexAttribArray(3);

	glBindVertexArray(0);
}

glm::mat4 Plane::computeShadowMatrix(glm::vec4 lightSource, float D)
{
	GLfloat xL = lightSource.x;
	GLfloat yL = lightSource.y;
	GLfloat zL = lightSource.z;

	glm::mat4 shadowMatrix;

	shadowMatrix[0][0] = B * yL + C * zL + D; shadowMatrix[0][1] = -B * xL;                   // First row
	shadowMatrix[0][2] = -C * xL;             shadowMatrix[0][3] = -D * xL;

	shadowMatrix[1][0] = -A * yL;             shadowMatrix[1][1] = A * xL + C * zL + D;       // Second row
	shadowMatrix[1][2] = -C * yL;             shadowMatrix[1][3] = -D * yL;

	shadowMatrix[2][0] = -A * zL;             shadowMatrix[2][1] = -B * zL;					  // Third row
	shadowMatrix[2][2] = A * xL + B * yL + D; shadowMatrix[2][3] = -D * zL;

	shadowMatrix[3][0] = -A;                  shadowMatrix[3][1] = -B;
	shadowMatrix[3][2] = -D;                  shadowMatrix[3][3] = A * yL + B * yL + C * zL;   // Fourth row

	return shadowMatrix;
}
