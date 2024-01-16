#ifndef MESH_H
#define MESH_H

#include "Shader.h"
#include <string>
#include <vector>
#include "glm/glm.hpp"


struct Vertex {
    glm::vec3 Position, Normal;
    glm::vec2 TexCoords;
};

struct Texture {
    unsigned int id;
    std::string type, path;
};

class Mesh {
public:
    std::vector<Vertex>       vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture>      textures;
    unsigned int VAO;

    // constructor
    Mesh(const std::vector<Vertex>&, const std::vector<unsigned int>&, std::vector<Texture>& textures);

    // deseneaza pe ecran mesh-ul
    void Draw(Shader& shader);

    // Setters
    void setVertices(const std::vector<Vertex>& newVertices);

private:
    unsigned int VBO, EBO;

    // initializeaza toate buffer-ele si array-ul de atribute
    void setupMesh();
};

#endif