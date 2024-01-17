#ifndef LEVELLOADER_H
#define LEVELLOADER_H

#include <vector>
#include "Model.h"

class LevelLoader
{
	std::vector<Model*> models;

public:
	// CONSTRUCTORS & DESTRUCTORS
	LevelLoader();
	~LevelLoader();

	// GETTERS & SETTERS
	Model* getModel(int index);
	void setModel(int index, Model* _model);

	// UTILS
	void loadModels(Shader* shader);
	void drawModels(Shader* shader);

	// TRANSFORMS

	void scaleModel(int index, GLfloat scaleFactor);
	void translateModel(int index, glm::vec3 dir);
	void rotateModel(int index, GLfloat deg, glm::vec3 dir, Shader* shader);
	void translate_scale_rotate(std::string modalPath, int index, glm::vec3 dir, GLfloat scaleFactor, GLfloat deg, glm::vec3 rotDir);
};

#endif 
