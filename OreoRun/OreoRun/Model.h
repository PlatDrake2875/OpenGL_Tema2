#ifndef MODEL_H
#define MODEL_H

#include "Mesh.h"
#include "stb_image.h"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

using verticesList = std::vector<std::vector<Vertex>>;

unsigned int TextureFromFile(const char* path, const std::string& directory);

class Model
{
    GLuint shaderProgram;
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    glm::quat cumulativeRotation;
    // datele modelului
    std::vector<Texture> textures_loaded;	// retine texturile incarcate, pentru a nu se incarca de mai multe ori aceeasi
    std::vector<Mesh> meshes;
    std::string directory;
    bool gammaCorrection;
    bool isLighted = true;
public:
    // constructor, expects a filepath to a 3D model.
    Model(const std::string& path, bool isSkyBox = false, bool gamma = false);
    Model() : gammaCorrection(false), shaderProgram(0), cumulativeRotation(glm::quat(1.f, 0.f, 0.f, 0.f)) {
        std::cerr << glm::to_string(cumulativeRotation) << '\n';
        setLighted(false);
    }
    Model(const Model& other)
        : textures_loaded(other.textures_loaded),
        meshes(other.meshes),
        directory(other.directory), 
        gammaCorrection(other.gammaCorrection),
        shaderProgram(other.shaderProgram),
        cumulativeRotation(other.cumulativeRotation) {
    }
    Model& operator=(const Model& other);

    // DRAW METHOD
    void Draw(Shader& shader);

    // GETTERS
    std::vector<std::vector<Vertex>> GetVerticesOfEachMesh() const;
    
    // SETTERS
    void setMeshesVertices(const std::vector<std::vector<Vertex>>& newMeshesVertices);
    void setShaderProgram(GLuint program) { shaderProgram = program; }
    void updateModelMatrix();

    // TRANSFORMATIONS
    void translate(glm::vec3 dir);
    void rotate(GLfloat deg, glm::vec3 dir);
    void scale(GLfloat scaleFactor);
    void rotateThenTranslate(GLfloat deg, glm::vec3 axis, glm::vec3 dir);

    // UTIL METHODS
    glm::vec3 calculateModelCenter() const;

private:
    void loadModel(std::string const& path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, const std::string& typeName);
    void setLighted(bool);  
};

#endif