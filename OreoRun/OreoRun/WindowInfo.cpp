#include "WindowInfo.h"

namespace WindowInfo {
	int baseWidth = 1280, baseHeight = 720;
	int winWidth = baseWidth, winHeight = baseHeight;

	int centerX() {
		return winWidth / 2;
	}

	int centerY() {
		return winHeight / 2;
	}
}