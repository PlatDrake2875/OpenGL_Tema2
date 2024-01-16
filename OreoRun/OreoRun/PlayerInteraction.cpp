#include "PlayerInteraction.h"

namespace PlayerInteraction
{
	Camera* camera = nullptr;
	bool isPlayerInteracting = true;

	void ProcessSpecialKeys(int key, int xx, int yy)
	{
		if (!isPlayerInteracting)
			return;

		camera->ProcessSpecialKeys(key, xx, yy);
	}

	void ProcessNormalKeys(unsigned char key, int x, int y)
	{
		static bool isFullScreen = false;

		if(!isPlayerInteracting)
			return;

		switch(key) {
			case 27:
				glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
				isPlayerInteracting = false;
				break;
			case 'f':
				if (!isFullScreen) {
					std::cout << "fullscreen" << std::endl;
					glutFullScreen();
					isFullScreen = true;
				}
				else {
					std::cout << "windowed" << std::endl;
					glutReshapeWindow(WindowInfo::baseWidth, WindowInfo::baseHeight);
					glutPositionWindow(50, 50);
					isFullScreen = false;
				}
				
				break;
		}

	}

	void MouseWheelFunction(int button, int dir, int x, int y)
	{
		if(!isPlayerInteracting)
			return;
		camera->mouseWheelFunction(button, dir, x, y);
	}

	void MouseMotionFunction(int x, int y)
	{
		if (!isPlayerInteracting)
			return;
		camera->mouseMotionFunction(x, y);
	}

	void HandleMouseClick(int button, int state, int x, int y) {
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {  // Check if mouse button is pressed down
			// Hide the cursor when clicked inside the window
			glutSetCursor(GLUT_CURSOR_NONE);
			isPlayerInteracting = true;
		}
	}

	void ReshapeWindowFunction(GLint newWidth, GLint newHeight)
	{
		glViewport(0, 0, newWidth, newHeight);
		WindowInfo::winWidth = newWidth;
		WindowInfo::winHeight = newHeight;
		std::cout << "New width: " << newWidth << " New height: " << newHeight << std::endl;
		camera->setViewWidthAndHeight(newWidth, newHeight);
	}
};
