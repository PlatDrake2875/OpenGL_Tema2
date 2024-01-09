#include "PlayerMovement.h"

Model* PlayerMovement::getPlayer()
{
	return player;
}

void PlayerMovement::setPlayer(Model* _player)
{
	if (_player == nullptr)
		return;
	player = _player;
}

void PlayerMovement::ProcessNormalKeys(unsigned char key, int x, int y)
{
	switch(key){
	case 'w':
		dir = glm::vec3(0.f, 0.f, 1.f);
		break;
	case 's':
		dir = glm::vec3(0.f, 0.f, -1.f);
		break;
	case 'a':
		dir = glm::vec3(1.f, 0.f, 0.f);
		break;
	case 'd':
		dir = glm::vec3(-1.f, 0.f, 0.f);
		break;
	case ' ':
		dir = glm::vec3(0.f, 1.f, 0.f);
		break;
	}
	updatePlayerPosition();
}

/// <summary>
/// Move the Oreo in the wanted direction and rotate it
/// </summary>
void PlayerMovement::updatePlayerPosition()
{
	player->rotate(5.f, glm::vec3(0.f, 1.f, 0.f));
	player->translate(dir);
}


