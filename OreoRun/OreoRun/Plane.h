#include <glm/ext/vector_float4.hpp>
#ifndef PLANE_H
#define PLANE_H

#include "SimpleShape.h"

class Plane : public SimpleShape
{
	glm::vec4 point1, point2, point3, point4;
public:
	float a, b, c, d; // ax + by + cz + d = 0
	// Creeaza plan (DREPTUNGHI) cu 4 puncte date (aveti grija ca punctele sa fie coplanare si sa fie intr-o ordine CONVEXA)
	Plane(const glm::vec4& p1, const glm::vec4& p2, const glm::vec4& p3, const glm::vec4& p4);
};

#endif // !PLANE_H



