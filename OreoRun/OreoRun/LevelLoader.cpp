#include "LevelLoader.h"
#include <iostream>
//#include <cstring>

LevelLoader::LevelLoader()
{
	
}

/// <summary>
/// Returns the model on position index
/// </summary>
/// <param name="index:"> position of the model</param>
/// <returns>Model* object </returns>
Model* LevelLoader::getModel(int index)
{
	if (index < 0 || index > models.size())
	{
		std::cerr << "Bro what u doin? You're out of bounds.\n";
		return nullptr;
	}

	return models[index];
}

void LevelLoader::setModel(int index, Model* _model)
{
	models[index] = _model;
}

void LevelLoader::translate_scale_rotate(std::string modalPath, int index, glm::vec3 dir, GLfloat scaleFactor, GLfloat deg, glm::vec3 rotDir)
{
	models.push_back(new Model(modalPath));
	models[index]->translate(dir);
	models[index]->scale(scaleFactor);
	models[index]->rotate(deg, rotDir);
}

void LevelLoader::loadModels(Shader* shader)
{
	models.push_back(new Model("models/oreo/oreo_4.gltf")); // Oreo King
	//models.push_back(new Model("models/christmas_ball/scene.gltf")); // Test christmas ball
	models.push_back(new Model("skyboxes/skybox_1/scene.gltf", true)); // Oreo King

	translate_scale_rotate("models/candy_cane/scene.gltf", 
		2, 
		glm::vec3(0.f, 100.f, 0.f), 
		60.f, 
		0, glm::vec3(1.0f, 0.f, 0.f));  // Candy cane
	translate_scale_rotate("models/christmas_ball/scene.gltf", 3, glm::vec3(100.f, -200.f, 0.f), 20.f, 0, glm::vec3(1.f, 0.f, 0.f));  // Christmas ball
	translate_scale_rotate("models/gingerbread_house/scene.gltf", 4, glm::vec3(150.f, 0.f, 0.f), 30.f, 175, glm::vec3(0.f, 1.f, 1.2f));  // Gingerbread house
	translate_scale_rotate("models/gingerbread_house_1/scene.gltf", 5, glm::vec3(-300.f, 0.f, -100.f), 5.f, 175, glm::vec3(0.f, 1.f, 1.2f));  // Gingerbread house
	translate_scale_rotate("models/milkbox/scene.gltf", 6, glm::vec3(100.f, 200.f, 0.f), 20.f, 0, glm::vec3(1.f, 0.f, 0.f));  // Milkbox
	//translate_scale_rotate("models/oreo_cupcake/scene.gltf", 7, glm::vec3(-100.f, -200.f, 0.f), 0.1f, 20, glm::vec3(0.f, 0.f, 0.f));  // Oreocupcake


	for (auto& model : models)
		model->setShaderProgram(shader->ID);
}

void LevelLoader::drawModels(Shader* shader)
{
	for (auto model : models) {
		if(model->isSkyBox)
			model->DrawSkyBox(*shader);
		else
			model->Draw(*shader);
	}
		
}

void LevelLoader::scaleModel(int index, GLfloat scaleFactor)
{
	models[index]->scale(scaleFactor);
}

void LevelLoader::translateModel(int index, glm::vec3 dir)
{
	models[index]->translate(dir);
}

void LevelLoader::rotateModel(int index, GLfloat deg, glm::vec3 dir, Shader* shader)
{
	models[index]->rotate(deg, dir);
}

LevelLoader::~LevelLoader()
{
	for (auto& model: models)
		delete model;
}
