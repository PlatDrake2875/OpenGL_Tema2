#ifndef CAMERA_H
#define CAMERA_H

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include <GL/freeglut.h>
#include "Constants.h"

class Camera
{
private: 
	glm::vec3 cameraPos, watchPoint, vertical;
	float alpha = 0.f, beta = 0.f, dist = 50.f;
	float incr_alpha1 = 0.1f, incr_alpha2 = 0.1f;
	float zNear = 1.f, width, height, fov = 30.f;

public:
	Camera(const glm::vec3& cameraPos, const glm::vec3& watchPoint, const glm::vec3& vertical, GLint winWidth, GLint winHeight);
	void ProcessNormalKeys(unsigned char key, int x, int y);
	void ProcessSpecialKeys(int key, int xx, int yy);
	void setPosition(const glm::vec3& newPos);
	void setWatchPoint(const glm::vec3& newWatchPoint);
	void setVertical(const glm::vec3& newPos);
	void setZNear(float newZNear);
	void setViewWidthAndHeight(float newWidth, float newHeight);
	void setFOV(float newFov);
	glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMatrix();
	void updateCamera();
};

#endif 

