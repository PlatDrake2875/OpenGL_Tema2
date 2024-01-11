#include "LevelLoader.h"

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

void LevelLoader::loadModels(Shader* shader)
{
	models.push_back(new Model("models/oreo/oreo_4.gltf")); // Oreo King
	models.push_back(new Model("models/christmas_ball/scene.gltf")); // Test christmas ball

	for (auto& model : models)
		model->setShaderProgram(shader->ID);
}

void LevelLoader::drawModels(Shader* shader)
{
	for (auto model : models)
		model->Draw(*shader);
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
