#pragma once
#include "Model.h"

class PlayerMovement {
	Model* player;
	glm::vec3 dir;
	glm::vec3 quaternionDir;

public:
	// CONSTRUCTORS & DESTRUCTORS
	PlayerMovement() : player(nullptr), dir(glm::vec3(0.f, 0.f, 0.f)) {};
	PlayerMovement(Model* _player, glm::vec3 _dir) :
		player(_player), dir(_dir) {};
	~PlayerMovement() { delete player; }

	// GETTERS & SETTERS
	Model* getPlayer();
	void setPlayer(Model* _player);

	// UTILS
	void ProcessNormalKeys(unsigned char key, int x, int y);
	void updatePlayerPosition();
};

