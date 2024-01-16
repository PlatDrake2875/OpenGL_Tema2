#include "Plane.h"

Plane::Plane(const glm::vec4& p1, const glm::vec4& p2, const glm::vec4& p3, const glm::vec4& p4) {
	point1 = p1;
	point2 = p2;
	point3 = p3;
	point4 = p4;
	a = p1.y * p2.z + p2.y * p3.z + p3.y * p1.z - p3.y * p2.z - p1.y * p3.z - p2.y * p1.z;
	b = -(p1.x * p2.z + p2.x * p3.z + p3.x * p1.z - p3.x * p2.z - p1.x * p3.z - p2.x * p1.z);
	c = p1.x * p2.y + p2.x * p3.y + p3.x * p1.y - p3.x * p2.y - p1.x * p3.y - p2.x * p1.y;
	d = -(p1.x * p2.y * p3.z + p2.x * p3.y * p1.z + p3.x * p1.y * p2.z -
		p3.x * p2.y * p1.z - p1.x * p3.y * p2.z - p2.x * p1.y * p3.z);
}

