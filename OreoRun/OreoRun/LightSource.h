
#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#include <glm/ext/vector_float3.hpp>
#include "Plane.h"
#include <glm/ext/matrix_float4x4.hpp>

class LightSource
{
public:
	glm::vec3 position, color;
	LightSource(const glm::vec3& pos, const glm::vec3& color = glm::vec3(1.0f, 1.0f, 1.0f));
	glm::mat4 getShadowMatrixOnPlane(const Plane& plane);
};
#endif

