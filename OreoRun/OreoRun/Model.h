#pragma once

#include "Mesh.h"
#include <vector>
#include <iostream>
#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include "stb_image.h"

unsigned int TextureFromFile(const char* path, const std::string& directory);

class Model
{
public:
    // datele modelului
    std::vector<Texture> textures_loaded;	// retine texturile incarcate, pentru a nu se incarca de mai multe ori aceeasi
    std::vector<Mesh> meshes;
    std::string directory;
    bool gammaCorrection;
    bool isLighted = true;

    // constructor, expects a filepath to a 3D model.
    Model(const std::string& path, const bool isSkyBox = false, const bool gamma = false);

    void Draw(Shader& shader);

private:
    void loadModel(std::string const& path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, const std::string& typeName);
    void setLighted(bool);  
};