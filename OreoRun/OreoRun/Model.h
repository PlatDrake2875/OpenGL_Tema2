#pragma once

#include "Mesh.h"
#include "stb_image.h"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <iostream>
#include <vector>

unsigned int TextureFromFile(const char* path, const std::string& directory);

class Model
{
public:
    // datele modelului
    std::vector<Texture> textures_loaded;	// retine texturile incarcate, pentru a nu se incarca de mai multe ori aceeasi
    std::vector<Mesh> meshes;
    std::string directory;
    bool gammaCorrection;

    // constructor, expects a filepath to a 3D model.
    Model(const std::string& path, const bool gamma = false);
    Model() : gammaCorrection(false) {
    }
    Model(const Model& other)
        : textures_loaded(other.textures_loaded),
        meshes(other.meshes),
        directory(other.directory),
        gammaCorrection(other.gammaCorrection) {
    }
    Model& operator=(const Model& other);

    // DRAW METHOD
    void Draw(Shader& shader);

    // UTIL METHODS
    std::vector<std::vector<Vertex>> GetVerticesOfEachMesh() const;

    // SETTERS
    void setMeshesVertices(const std::vector<std::vector<Vertex>>& newMeshesVertices);


private:
    void loadModel(std::string const& path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, const std::string& typeName);
};