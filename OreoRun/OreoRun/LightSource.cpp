#include "LightSource.h"

LightSource::LightSource(const glm::vec3& pos, const glm::vec3& color)
{
	this->position = pos;
	this->color = color;
}

//! Implement this function
glm::mat4 LightSource::getShadowMatrixOnPlane(const Plane& plane)
{
	return glm::mat4();
}
