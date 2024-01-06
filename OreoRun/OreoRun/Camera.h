#ifndef CAMERA_H
#define CAMERA_H

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include <GL/freeglut.h>
#include "Constants.h"
#include "WindowInfo.h"
#include <iostream>

class Camera
{
private: 
	glm::vec3 cameraPos, watchPoint, vertical;
	float alpha = 0.f, beta = 0.f, dist = 50.f;
	float betaSensitivity = 0.001f, alphaSensitivity = betaSensitivity;
	float zNear = 1.f, width, height, fov = 30.f;
	int lastMouseX = 0, lastMouseY = 0;
	static const float minDist, maxDist;
public:
	Camera(const glm::vec3& cameraPos, const glm::vec3& watchPoint, const glm::vec3& vertical, float winWidth, float winHeight);
	void ProcessSpecialKeys(int key, int xx, int yy);
	void mouseWheelFunction(int button, int dir, int x, int y);
	void mouseMotionFunction(int x, int y);
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

