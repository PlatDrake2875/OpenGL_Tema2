#include "Camera.h"

Camera::Camera(const glm::vec3& cameraPos, const glm::vec3& watchPoint, const glm::vec3& vertical, GLint winWidth, GLint winHeight) {
	this->cameraPos = glm::vec3(cameraPos);
	this->watchPoint = glm::vec3(watchPoint);
	this->vertical = glm::vec3(vertical);
	this->width = winWidth;
	this->height = winHeight;
}

void Camera::ProcessNormalKeys(unsigned char key, int x, int y)
{
	switch (key) {			
		case '-':
			dist -= 5.0;
			break;
		case '+':
			dist += 5.0;
			break;
	}
	if (key == 27)
		exit(0);
}

void Camera::ProcessSpecialKeys(int key, int xx, int yy)
{
	switch (key)
	{
		case GLUT_KEY_LEFT:
			beta -= 0.1f;
			break;
		case GLUT_KEY_RIGHT:
			beta += 0.1f;
			break;
		case GLUT_KEY_UP:
			alpha += incr_alpha1;
			incr_alpha2 = abs(alpha + Constants::PI / 2) < 0.05 ? 0.f : 0.1f;
			break;
		case GLUT_KEY_DOWN:
			alpha -= incr_alpha2;
			incr_alpha2 = abs(alpha + Constants::PI / 2) < 0.05 ? 0.f : 0.1f;
			break;
	}
}

void Camera::setPosition(const glm::vec3& newPos)
{
	this->cameraPos = glm::vec3(newPos);
}

void Camera::setWatchPoint(const glm::vec3& newWatchPoint)
{
	this->watchPoint = glm::vec3(newWatchPoint);
}

void Camera::setVertical(const glm::vec3& newPos)
{
	this->vertical = glm::vec3(newPos);
}

void Camera::updateCamera()
{
	cameraPos.x = watchPoint.x + dist * cos(alpha) * cos(beta);
	cameraPos.y = watchPoint.y + dist * cos(alpha) * sin(beta);
	cameraPos.z = watchPoint.z + dist * sin(alpha);
}

void Camera::setZNear(float newZNear)
{
	this->zNear = zNear;
}

void Camera::setViewWidthAndHeight(GLint newWidth, GLint newHeight)
{
	this->width = newWidth;
	this->height = newHeight;
}

void Camera::setFOV(float)
{
	this->fov = fov;
}

glm::mat4 Camera::getViewMatrix() const
{
	return glm::lookAt(cameraPos, watchPoint, vertical);
}

glm::mat4 Camera::getProjectionMatrix()
{
	return glm::infinitePerspective(fov, GLfloat(width) / GLfloat(height), zNear);
}
