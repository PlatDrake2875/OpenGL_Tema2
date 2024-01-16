#include "Camera.h"

const float Camera::minDist = 50.f;
const float Camera::maxDist = 300.f;

Camera::Camera(const glm::vec3& cameraPos, const glm::vec3& watchPoint, const glm::vec3& vertical, GLint winWidth, GLint winHeight) {
	this->cameraPos = glm::vec3(cameraPos);
	this->watchPoint = glm::vec3(watchPoint);
	this->vertical = glm::vec3(vertical);
	this->width = winWidth;
	this->height = winHeight;
}

void Camera::ProcessSpecialKeys(int key, int xx, int yy)
{
	
}

void Camera::mouseWheelFunction(int button, int dir, int x, int y)
{
	
	if (dir > 0 && dist > minDist)
	{
		dist -= 5.0;
	}
	else if(dir < 0 && dist < maxDist)
	{
		dist += 5.0;
	}
}

void Camera::setPosition(const glm::vec3& newPos)
{
	this->cameraPos = glm::vec3(newPos);
}

void Camera::mouseMotionFunction(int x, int y)
{
	// calculam diferenta de coordonate ale mouse-ului de la ultima apelare
	int deltaX = x - lastMouseX;
	int deltaY = y - lastMouseY;

	bool edgeCaseX = false;
	bool edgeCaseY = false;

	if (x <= 1 || x >= WindowInfo::winWidth - 1) {
		glutWarpPointer(WindowInfo::centerX(), y);

		// salvam noile coordonate ale mouse-ului
		lastMouseX = WindowInfo::centerX();
		lastMouseY = y;

		edgeCaseX = true;
	}

	if (y <= 50 || y >= WindowInfo::winHeight - 50) { // 50 este un safety margin pentru a nu da de situatii ciudate
		glutWarpPointer(x, WindowInfo::centerY());

		lastMouseX = x;
		lastMouseY = WindowInfo::centerY();

		edgeCaseY = true;
	}

	// actualizam unghiurile de rotatie ale camerei si salvam noile pozitii ale mouse-ului
	if (!edgeCaseX) {
		beta += deltaX * betaSensitivity;
		lastMouseX = x;
	}
		
	if (!edgeCaseY) {
		float newAlpha = alpha + deltaY * alphaSensitivity;
		if (newAlpha > 0.1 && newAlpha < Constants::PI / 2 - 0.1)
		{
			alpha = newAlpha;
			lastMouseY = y;
		}
	}
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
