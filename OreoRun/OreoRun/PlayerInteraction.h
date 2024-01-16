
#ifndef PLAYERINTERACTION_H
#define PLAYERINTERACTION_H

#include "Camera.h"
#include "PlayerMovement.h"
#include <GL/freeglut.h>
#include <iostream>

namespace PlayerInteraction
{
	extern Camera* camera;
	extern bool isPlayerInteracting;
	extern PlayerMovement* playerMov;
	extern void ProcessSpecialKeys(int key, int xx, int yy);
	extern void MouseWheelFunction(int button, int dir, int x, int y);
	extern void MouseMotionFunction(int x, int y);
	extern void ProcessNormalKeys(unsigned char key, int x, int y);
	extern void HandleMouseClick(int button, int state, int x, int y);
	extern void ReshapeWindowFunction(GLint newWidth, GLint newHeight);
};

#endif 
